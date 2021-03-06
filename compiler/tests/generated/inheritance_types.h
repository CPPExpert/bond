
#pragma once

#include <bond/core/bond_version.h>

#if BOND_VERSION < 0x0520
#error This file was generated by a newer version of the Bond compiler and is incompatible with your version of the Bond library.
#endif

#if BOND_MIN_CODEGEN_VERSION > 0x0900
#error This file was generated by an older version of the Bond compiler and is incompatible with your version of the Bond library.
#endif

#include <bond/core/config.h>
#include <bond/core/containers.h>



namespace tests
{
    
    struct Base
    {
        int32_t x;
        
        Base()
          : x()
        {
        }

        
#ifndef BOND_NO_CXX11_DEFAULTED_FUNCTIONS
        // Compiler generated copy ctor OK
        Base(const Base&) = default;
#endif
        
#if !defined(BOND_NO_CXX11_DEFAULTED_MOVE_CTOR)
        Base(Base&&) = default;
#elif !defined(BOND_NO_CXX11_RVALUE_REFERENCES)
        Base(Base&& other)
          : x(std::move(other.x))
        {
        }
#endif
        
        
#ifndef BOND_NO_CXX11_DEFAULTED_FUNCTIONS
        // Compiler generated operator= OK
        Base& operator=(const Base&) = default;
#endif

        bool operator==(const Base& other) const
        {
            return true
                && (x == other.x);
        }

        bool operator!=(const Base& other) const
        {
            return !(*this == other);
        }

        void swap(Base& other)
        {
            using std::swap;
            swap(x, other.x);
        }

        struct Schema;

    protected:
        void InitMetadata(const char*, const char*)
        {
        }
    };

    inline void swap(::tests::Base& left, ::tests::Base& right)
    {
        left.swap(right);
    }

    
    struct Foo
      : ::tests::Base
    {
        int32_t x;
        
        Foo()
          : x()
        {
        }

        
#ifndef BOND_NO_CXX11_DEFAULTED_FUNCTIONS
        // Compiler generated copy ctor OK
        Foo(const Foo&) = default;
#endif
        
#if !defined(BOND_NO_CXX11_DEFAULTED_MOVE_CTOR)
        Foo(Foo&&) = default;
#elif !defined(BOND_NO_CXX11_RVALUE_REFERENCES)
        Foo(Foo&& other)
          : ::tests::Base(std::move(other)),
            x(std::move(other.x))
        {
        }
#endif
        
        
#ifndef BOND_NO_CXX11_DEFAULTED_FUNCTIONS
        // Compiler generated operator= OK
        Foo& operator=(const Foo&) = default;
#endif

        bool operator==(const Foo& other) const
        {
            return true
                && (static_cast<const ::tests::Base&>(*this) == static_cast<const ::tests::Base&>( other))
                && (x == other.x);
        }

        bool operator!=(const Foo& other) const
        {
            return !(*this == other);
        }

        void swap(Foo& other)
        {
            using std::swap;
            ::tests::Base::swap( other);
            swap(x, other.x);
        }

        struct Schema;

    protected:
        void InitMetadata(const char*name, const char*qual_name)
        {
            ::tests::Base::InitMetadata(name, qual_name);
        }
    };

    inline void swap(::tests::Foo& left, ::tests::Foo& right)
    {
        left.swap(right);
    }
} // namespace tests

