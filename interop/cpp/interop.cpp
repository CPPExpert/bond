#include <stdio.h>
#include <string.h>

#include <bond/core/bond.h>
#include <bond/stream/stdio_output_stream.h>

#include "gen/interop_reflection.h"
#include "gen/interop_apply.h"

using namespace com::microsoft::bond::interop;

int main(int argc, char ** argv) {
    if (argc != 3) {
        printf("Usage: interop read|write file\n");
        return 255;
    }

    bool read_mode = false;
    if (strcmp(argv[1], "read") == 0) {
        read_mode = true;
    } else if (strcmp(argv[1], "write") == 0) {
        read_mode = false;
    } else {
        printf("Unknown mode: %s\n", argv[1]);
        return 255;
    }

    char * fpath = argv[2];

    if (read_mode) {
        const size_t buf_len = 1024 * 1024;
        void* buffer = malloc(buf_len);
        FILE* d = fopen(fpath, "rb");
        size_t size = fread(buffer, 1, buf_len, d);
        fclose(d);

        if (size == buf_len) {
            printf("Buffer was completely filled with serialized data.");
            printf("It is very likely that you didn't read the full object!");
        }

        OneOfEverything ooe;
        bond::InputBuffer input(buffer, size);
        Unmarshal(input, ooe);

        printf("ooe.b: %d\n", ooe.b);
        printf("ooe.s: %d\n", ooe.s);
        printf("ooe.i: %d\n", ooe.i);
        printf("ooe.l: %ld\n", ooe.l);
        printf("ooe.ub: %u\n", ooe.ub);
        printf("ooe.us: %u\n", ooe.us);
        printf("ooe.ui: %u\n", ooe.ui);
        printf("ooe.ul: %lu\n", ooe.ul);
        printf("ooe.f: %f\n", ooe.f);
        printf("ooe.d: %f\n", ooe.d);
        printf("ooe.bl: %s\n", ooe.bl ? "true" : "false");
        printf("ooe.str: %s\n", ooe.str.c_str());
        printf("ooe.wstr: %S\n", ooe.wstr.c_str());
        printf("ooe.l_b:\n");
        for (std::list<int8_t>::iterator i = ooe.l_b.begin();
             i != ooe.l_b.end();
             i++) {
            printf("\t%d\n", *i);
        }
        printf("ooe.v_f:\n");
        for (std::vector<int16_t>::iterator i = ooe.v_s.begin();
             i != ooe.v_s.end();
             i++) {
            printf("\t%d\n", *i);
        }
        printf("ooe.s_ui:\n");
        for (std::set<uint32_t>::iterator i = ooe.s_ui.begin();
             i != ooe.s_ui.end();
             i++) {
            printf("\t%u\n", *i);
        }
        printf("ooe.m_i_str:\n");
        for (std::map<int32_t, std::string>::iterator i = ooe.m_i_str.begin();
             i != ooe.m_i_str.end();
             i++) {
            printf("\t%d -> %s\n", i->first, i->second.c_str());
        }
        printf("ooe.e: %u\n", ooe.e);
        printf("ooe.oos.str: %s\n", ooe.oos.str.c_str());
    } else {
        OneOfEverything ooe;
        ooe.b = 3;
        ooe.s = 333;
        ooe.i = 333333;
        ooe.l = 33333333333;
        ooe.ub = 128;
        ooe.us = 32768;
        ooe.ui = 2147483648;
        // 9223372036854775808, in hex, to avoid a warning.
        ooe.ul = 0x8000000000000000;
        ooe.f = .5;
        ooe.d = .5;
        ooe.bl = true;
        ooe.str = "three";
        ooe.wstr = L"threeeee";
        ooe.l_b.push_back(3);
        ooe.l_b.push_back(33);
        ooe.v_s.push_back(3);
        ooe.v_s.push_back(33);
        ooe.s_ui.insert(3);
        ooe.s_ui.insert(33);
        ooe.s_ui.insert(333);
        ooe.m_i_str.emplace(1, "one");
        ooe.m_i_str.emplace(2, "two");
        ooe.m_i_str.emplace(3, "three");
        ooe.m_i_str.emplace(4, "four");
        ooe.m_i_str.emplace(5, "five");
        ooe.e = com::microsoft::bond::interop::_bond_enumerators::SomeEnum::B;
        ooe.oos.str = "one of something, anyway";

        FILE* d = fopen(fpath, "wb");
        bond::StdioOutputStream output(d);
        bond::FastBinaryWriter<bond::StdioOutputStream> writer(output);
        Marshal(ooe, writer);
        fclose(d);
    }
    return 0;
}