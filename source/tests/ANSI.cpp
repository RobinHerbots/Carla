/*
 * Carla Tests
 * Copyright (C) 2013 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * For a full copy of the GNU General Public License see the doc/GPL.txt file.
 */

#undef NDEBUG
#undef DEBUG
#define DEBUG 1

#define RING_BUFFER_SIZE 48

// 0 - base
// 1 - utils
// 2 - engine
// 3 - plugin
// 4 - standalone
#define ANSI_TEST_N 0

#if ANSI_TEST_N == 0
// utils
#include "CarlaUtils.hpp"

// Carla Backend API
#include "CarlaBackend.hpp"
#endif

#if ANSI_TEST_N == 1
// includes
#include "CarlaDefines.hpp"
#include "CarlaMIDI.h"
#include "ladspa_rdf.hpp"
#include "lv2_rdf.hpp"

// Carla Backend API
#include "CarlaBackend.hpp"

// Carla utils (part 1/4)
#include "CarlaUtils.hpp"
#include "CarlaJuceUtils.hpp"

// Carla utils (part 2/4)
#include "CarlaMutex.hpp"
#include "CarlaRingBuffer.hpp"
#include "CarlaString.hpp"
#include "RtList.hpp"

// Carla utils (part 3/4)
#include "CarlaBackendUtils.hpp"
#include "CarlaBridgeUtils.hpp"
#include "CarlaLadspaUtils.hpp"
#include "CarlaLibUtils.hpp"
#include "CarlaLv2Utils.hpp"
#include "CarlaOscUtils.hpp"
#include "CarlaShmUtils.hpp"
#include "CarlaStateUtils.hpp"
#include "CarlaVstUtils.hpp"

// Carla utils (part 4/4)
#include "Lv2AtomQueue.hpp"

// Carla Native Plugin API
#include "CarlaNative.h"

// Carla Native Plugin API (C++)
#include "CarlaNative.hpp"

// Carla Plugin API
#include "CarlaPlugin.hpp"

// Carla Engine API
#include "CarlaEngine.hpp"

// Carla Host API
#include "CarlaHost.hpp"
// ANSI_TEST_N == 1
#endif

#if ANSI_TEST_N == 2
// Carla Engine
#include "engine/CarlaEngineThread.hpp"
#endif

#if ANSI_TEST_N == 3
// Carla Plugin
#include "plugin/CarlaPluginThread.hpp"
#include "plugin/CarlaPluginInternal.hpp"
#endif

#if ANSI_TEST_N == 4
// Carla Host Standalone
#include "CarlaHost.hpp"
#include "CarlaUtils.hpp"
#endif

#if ANSI_TEST_N == 1
// -----------------------------------------------------------------------

namespace CB = CarlaBackend;
using juce::ScopedPointer;

int safe_assert_return_test(bool test)
{
    CARLA_SAFE_ASSERT_RETURN(test, 1);
    return 0;
}
#endif

// -----------------------------------------------------------------------

int main()
{
#if ANSI_TEST_N == 0
    CARLA_BACKEND_USE_NAMESPACE

    BinaryType b;
    CallbackType c;
    CARLA_ASSERT(sizeof(b) == sizeof(BinaryType));
    CARLA_ASSERT(sizeof(b) == sizeof(int));
    CARLA_ASSERT(sizeof(BinaryType) == sizeof(int));

    CARLA_ASSERT(sizeof(c) == sizeof(CallbackType));
    CARLA_ASSERT(sizeof(c) == sizeof(int));
    CARLA_ASSERT(sizeof(CallbackType) == sizeof(int));
#endif

#if ANSI_TEST_N == 1
    // ladspa rdf
    {
        LADSPA_RDF_ScalePoint a;
        LADSPA_RDF_Port b;
        LADSPA_RDF_Descriptor c;
    }

    // lv2 rdf
    {
        LV2_RDF_PortMidiMap a;
        LV2_RDF_PortPoints b;
        LV2_RDF_PortUnit c;
        LV2_RDF_PortScalePoint d;
        LV2_RDF_Port e;
        LV2_RDF_Preset f;
        LV2_RDF_Feature g;
        LV2_RDF_UI h;
        LV2_RDF_Descriptor i;
    }

    // Carla Backend API
    {
        CB::BinaryType a = CB::BINARY_NONE;
        CB::PluginType b = CB::PLUGIN_NONE;
        CB::PluginCategory c = CB::PLUGIN_CATEGORY_NONE;
        CB::ParameterType d = CB::PARAMETER_UNKNOWN;
        CB::InternalParametersIndex e = CB::PARAMETER_NULL;
        CB::PatchbayIconType f = CB::PATCHBAY_ICON_APPLICATION;
        CB::OptionsType g = CB::OPTION_PROCESS_NAME;
        CB::CallbackType h = CB::CALLBACK_DEBUG;
        CB::ProcessMode i = CB::PROCESS_MODE_SINGLE_CLIENT;
        CB::TransportMode j = CB::TRANSPORT_MODE_INTERNAL;
        CB::CallbackFunc k = nullptr;
        CB::ParameterData l;
        CB::ParameterRanges m;
        CB::MidiProgramData n;
        CB::CustomData o;
        a=a;b=b;c=c;d=d;e=e;f=f;g=g;h=h;i=i;j=j;k=k;l=l;m=m;n=n;o=o;
    }

    // Carla Native Plugin API
    {
        HostHandle a = nullptr;
        PluginHandle b = nullptr;
        PluginCategory c = PLUGIN_CATEGORY_NONE;
        PluginHints d = static_cast<PluginHints>(0x0);
        PluginSupports e = static_cast<PluginSupports>(0x0);
        ParameterHints f = static_cast<ParameterHints>(0x0);
        PluginDispatcherOpcode g = PLUGIN_OPCODE_NULL;
        HostDispatcherOpcode h = HOST_OPCODE_NULL;
        ParameterScalePoint i;
        ParameterRanges j;
        Parameter k;
        MidiEvent l;
        MidiProgram m;
        TimeInfoBBT n;
        TimeInfo o;
        HostDescriptor p;
        PluginDescriptor q = { c, d, e,
                               0, 0, 0, 0, 0, 0,
                               nullptr, nullptr, nullptr, nullptr,
                               nullptr, nullptr,
                               nullptr, nullptr, nullptr, nullptr,
                               nullptr, nullptr,
                               nullptr, nullptr, nullptr,
                               nullptr, nullptr,
                               nullptr, nullptr, nullptr,
                               nullptr, nullptr, nullptr,
                               nullptr, nullptr,
                               nullptr };
        a=a;b=b;c=c;d=d;e=e;f=f;g=g;h=h;i=i;j=j;k=k;l=l;m=m;n=n;o=o;p=p;
        (void)q;
    }

    // Carla common utils
    {
        bool2str(true);
        pass();
        carla_debug("DEBUG");
        carla_stdout("OUT");
        carla_stderr("ERR");
        carla_stderr2("ERR2");
        carla_sleep(1);
        carla_msleep(1);
        carla_setenv("x", "y");
        carla_setprocname("ANSI-Test");

        assert(safe_assert_return_test(true) == 0);
        assert(safe_assert_return_test(false) == 1);

        // carla_strdup
        {
            const char* s1 = carla_strdup("s1");
            const char* s2 = carla_strdup_free(strdup("s2"));
            delete[] s1;
            delete[] s2;
        }

        // carla_min
        {
            assert(carla_min<int>( 1,  2, -1) ==  1);
            assert(carla_min<int>( 1,  2,  0) ==  1);
            assert(carla_min<int>( 1,  2,  1) ==  1);
            assert(carla_min<int>( 1,  2,  2) ==  2);
            assert(carla_min<int>( 1,  2,  3) ==  3);

            assert(carla_min<int>( 2,  2, -1) ==  2);
            assert(carla_min<int>( 1,  2, -1) ==  1);
            assert(carla_min<int>( 0,  2, -1) ==  0);
            assert(carla_min<int>(-1,  2, -1) == -1);
            assert(carla_min<int>(-2,  2, -1) == -1);

            assert(carla_min<int>(-1,  2,  0) ==  0);
            assert(carla_min<int>(-1,  1,  0) ==  0);
            assert(carla_min<int>(-1,  0,  0) ==  0);
            assert(carla_min<int>(-1, -1,  0) ==  0);
            assert(carla_min<int>(-1, -2,  0) ==  0);

            unsigned u1 = static_cast<unsigned>(-1);
            unsigned u2 = static_cast<unsigned>(-2);

            assert(carla_min<unsigned>(u1, u2,  0) == u2);
            assert(carla_min<unsigned>(u1, u2, u1) == u1);
            assert(carla_min<unsigned>(u1, u2, u2) == u2);

            assert(carla_min<unsigned>(u1,  2,  0) == 2);
            assert(carla_min<unsigned>( 2, u1,  0) == 2);
            assert(carla_min<unsigned>( 2,  2, u1) == u1);
        }

        // carla_max (same as min)
        {
            assert(carla_max<int>( 1,  2, -1) == -1);
            assert(carla_max<int>( 1,  2,  0) ==  0);
            assert(carla_max<int>( 1,  2,  1) ==  1);
            assert(carla_max<int>( 1,  2,  2) ==  2);
            assert(carla_max<int>( 1,  2,  3) ==  2);

            assert(carla_max<int>( 2,  2, -1) == -1);
            assert(carla_max<int>( 1,  2, -1) == -1);
            assert(carla_max<int>( 0,  2, -1) == -1);
            assert(carla_max<int>(-1,  2, -1) == -1);
            assert(carla_max<int>(-2,  2, -1) == -1);

            assert(carla_max<int>(-1,  2,  0) ==  0);
            assert(carla_max<int>(-1,  1,  0) ==  0);
            assert(carla_max<int>(-1,  0,  0) ==  0);
            assert(carla_max<int>(-1, -1,  0) == -1);
            assert(carla_max<int>(-1, -2,  0) == -1);

            unsigned u1 = static_cast<unsigned>(-1);
            unsigned u2 = static_cast<unsigned>(-2);

            assert(carla_max<unsigned>(u1, u2,  0) == 0);
            assert(carla_max<unsigned>(u1, u2, u1) == u1);
            assert(carla_max<unsigned>(u1, u2, u2) == u2);

            assert(carla_max<unsigned>(u1,  2,  0) == 0);
            assert(carla_max<unsigned>( 2, u1,  0) == 0);
            assert(carla_max<unsigned>( 2,  2, u1) == 2);
        }
        // carla_fixValue (same as min)
        {
            assert(carla_fixValue<int>( 1,  2, -1) ==  1);
            assert(carla_fixValue<int>( 1,  2,  0) ==  1);
            assert(carla_fixValue<int>( 1,  2,  1) ==  1);
            assert(carla_fixValue<int>( 1,  2,  2) ==  2);
            assert(carla_fixValue<int>( 1,  2,  3) ==  2);

            assert(carla_fixValue<int>( 1,  2, -1) ==  1);
            assert(carla_fixValue<int>( 0,  2, -1) ==  0);
            assert(carla_fixValue<int>(-1,  2, -1) == -1);
            assert(carla_fixValue<int>(-2,  2, -1) == -1);

            assert(carla_fixValue<int>(-1,  2,  0) ==  0);
            assert(carla_fixValue<int>(-1,  1,  0) ==  0);
            assert(carla_fixValue<int>(-1,  0,  0) ==  0);

            unsigned u1 = static_cast<unsigned>(-1);
            unsigned u2 = static_cast<unsigned>(-2);

            assert(carla_fixValue<unsigned>(u2, u1,  0) == u2);
            assert(carla_fixValue<unsigned>(u2, u1, u1) == u1);
            assert(carla_fixValue<unsigned>(u2, u1, u2) == u2);
        }

        // carla_add (copy and fill are very similar, so they are ignored here)
        {
            int a = 0;
            int b = 1;
            int c = 2;

            carla_add<int>(&a, &a, 1);
            assert(a == 0);

            carla_add<int>(&a, &b, 1);
            assert(a == 1);

            carla_add<int>(&a, &c, 1);
            assert(a == 3);

            float d = 10.0f;
            float e = 0.11f;

            carla_add<float>(&d, &e, 1);
            assert(d == 10.11f);

            float f[5] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
            float g[5] = { 0.1f, 0.1f, 0.1f, 0.1f, 0.1f };

            carla_add<float>(f, g, 5);
            assert(f[0] == f[0]);
            assert(f[1] == f[1]);
            assert(f[2] == f[2]);
            assert(f[3] == f[3]);
            assert(f[4] == f[4]);
            assert(f[0] == g[0]);
            assert(f[1] == g[1]);
            assert(f[2] == g[2]);
            assert(f[3] == g[3]);
            assert(f[4] == g[4]);

            carla_add<float>(g, f, 1);
            carla_add<float>(g, f, 2);
            carla_addFloat(g, f, 3);
            carla_add(g, f, 4);
            carla_add(g, f, 5);
            assert(g[0] == f[0]*6);
            assert(g[1] == f[1]*5);
            assert(g[2] == f[2]*4);
            assert(g[3] == f[3]*3);
            assert(g[4] == f[4]*2);

            carla_stdout("f: %f,%f,%f,%f,%f", f[0], f[1], f[2], f[3], f[4]);

            assert(f[0] != g[0]);
            assert(f[1] != g[1]);
            assert(f[2] != g[2]);
            assert(f[3] != g[3]);
            assert(f[4] != g[4]);
            carla_copy(f, g, 3);
            assert(f[0] == g[0]);
            assert(f[1] == g[1]);
            assert(f[2] == g[2]);
            assert(f[3] != g[3]);
            assert(f[4] != g[4]);

            carla_stdout("f: %f,%f,%f,%f,%f", f[0], f[1], f[2], f[3], f[4]);
        }

        // memory functions
        {
            uint64_t a[100];
            uint64_t at = 9999;
            carla_fill<uint64_t>(a, 100, 1);
            assert(a[99] == 1);
            assert(at == 9999);
            carla_zeroMem(a, sizeof(uint64_t)*100);
            assert(a[0] == 0);
            assert(a[99] == 0);
            assert(at == 9999);

            uint64_t b[100];
            uint64_t bt = 9999;
            carla_fill<uint64_t>(b, 100, 2);
            assert(b[99] == 2);
            assert(at == 9999);
            carla_zeroStruct(b);
            assert(b[0] == 0);
            assert(b[99] == 0);
            assert(bt == 9999);

            uint64_t c[100];
            uint64_t ct = 9999;
            carla_fill<uint64_t>(c, 100, 3);
            assert(c[99] == 3);
            assert(at == 9999);
            carla_zeroStruct(c, 100);
            assert(c[0] == 0);
            assert(c[99] == 0);
            assert(ct == 9999);

            struct Test { bool b; void* p; int i; };
            Test d, e[11], f[9];
            carla_zeroStruct<Test>(d);
            carla_zeroStruct<Test>(e, 11);
            carla_zeroStruct<Test>(f, 9);

            Test* h(new Test);
            h->i = 9;
            carla_zeroStruct<Test>(h, 1);
            assert(h->i == 0);
            delete h;

            Test* i(new Test[2]);
            carla_zeroStruct<Test>(i, 2);
            delete[] i;
        }
    }

    // Carla misc utils imported from Juce source code
    {
        struct Test { char s[24]; void* p; };

        ScopedPointer<int> a(new int);
        ScopedPointer<long long> b(new long long);
        ScopedPointer<Test> c(new Test);
        ScopedPointer<Test> d(new Test);
        ScopedPointer<Test> e(new Test);
        e = nullptr;
        delete d.release();
        delete e.release();
        ScopedPointer<Test> f(nullptr);
    }

    // Carla Native Plugin API (C++)
    {
        class PluginClassTest : public PluginClass
        {
        public:
            PluginDescriptorClassTest(const HostDescriptor* const host)
                : PluginClass(host) {}
        protected:
            void process(float** const, float** const, const uint32_t, const MidiEvent* const, const uint32_t) {}

            PluginClassEND(PluginClassTest)
            CARLA_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginClassTest)
        };

        const HostDescriptor a = { nullptr, nullptr, nullptr,
                                   nullptr, nullptr, nullptr,
                                   nullptr, nullptr,
                                   nullptr, nullptr, nullptr, nullptr,
                                   nullptr, nullptr,
                                   nullptr };

        PluginDescriptor b = { PLUGIN_CATEGORY_NONE, PLUGIN_IS_RTSAFE, PLUGIN_SUPPORTS_EVERYTHING,
                               0, 0, 0, 0, 0, 0,
                               nullptr, nullptr, nullptr, nullptr,
                               PluginDescriptorFILL(PluginDescriptorClassTest) };
        (void)b;

        ScopedPointer<PluginDescriptorClassTest> c;
        c = new PluginDescriptorClassTest(&a);
    }

    // Carla Backend utils
    {
        class TestClass { public: int i; char pad[50]; };

        TestClass a, b, c;
        uintptr_t ad = CarlaBackend::getAddressFromPointer(&a);
        uintptr_t bd = CarlaBackend::getAddressFromPointer(&b);
        uintptr_t cd = CarlaBackend::getAddressFromPointer(&c);
        assert(bd > ad);
        assert(cd > bd);

        TestClass* ap = CarlaBackend::getPointerFromAddress<TestClass>(ad);
        TestClass* bp = CarlaBackend::getPointerFromAddress<TestClass>(bd);
        TestClass* cp = CarlaBackend::getPointerFromAddress<TestClass>(cd);
        assert(ap == &a);
        assert(bp == &b);
        assert(cp == &c);

        ap->i = 4;
        bp->i = 5;
        cp->i = 6;
        assert(a.i == 4);
        assert(b.i == 5);
        assert(c.i == 6);
    }

    // Carla Mutex
    {
        CarlaMutex m;
        m.tryLock();
        m.unlock();
        const CarlaMutex::ScopedLocker sl(m);
    }

    // RingBuffer
    {
        RingBuffer buf;
        RingBufferControl ctrl(&buf);

        assert(! ctrl.dataAvailable());
        assert(ctrl.readInt() == 0);
        assert(ctrl.readFloat() == 0.0f);
        assert(! ctrl.dataAvailable());

        ctrl.writeChar('z');
        ctrl.commitWrite();
        assert(ctrl.dataAvailable());
        const char c = ctrl.readChar();
        carla_stdout("BufRead c = \"%c\"", c);
        assert(c != '\0');
        assert(c == 'z');
        assert(! ctrl.dataAvailable());

        ctrl.writeInt(9999);
        ctrl.commitWrite();
        const int i = ctrl.readInt();
        carla_stdout("BufRead i = \"%i\"", i);
        assert(i != 0);
        assert(i == 9999);

        ctrl.writeLong(-88088);
        ctrl.commitWrite();
        const long l = ctrl.readLong();
        carla_stdout("BufRead l = \"%li\"", l);
        assert(l != 0);
        assert(l == -88088);

        ctrl.writeFloat(5.6789f);
        ctrl.commitWrite();
        const float f = ctrl.readFloat();
        carla_stdout("BufRead f = \"%f\"", f);
        assert(f != 0.0f);
        assert(f == 5.6789f);

        assert(! ctrl.dataAvailable());

        for (char i='1'; i <= 'z'; ++i)
        {
           ctrl.writeChar(char(i));
           ctrl.commitWrite();
        }

        assert(ctrl.dataAvailable());

        printf("CHAR DUMP:\n");

        while (ctrl.dataAvailable())
            printf("%c", ctrl.readChar());

        assert(! ctrl.dataAvailable());

        printf("\nDUMP FINISHED\n");
    }

    // RtList
    {
        class ListTester
        {
        public:
            struct CountObj {
                CountObj() : count(0) {}
                volatile int count;
            };

            ListTester()
            {
                ++getCounter().count;
            }

            ~ListTester()
            {
                --getCounter().count;
            }

            static CountObj& getCounter()
            {
                static CountObj counter;
                return counter;
            }
        };

        ListTester::CountObj& obj = ListTester::getCounter();
        assert(obj.count == 0);

        NonRtList<ListTester> list;
        obj = ListTester::getCounter();
        assert(obj.count == 1); // List fRetValue

        ListTester t1;
        obj = ListTester::getCounter();
        assert(obj.count == 2); // List fRetValue + t1

        list.append(t1);
        list.append(t1);
        list.append(t1);
        obj = ListTester::getCounter();
        assert(obj.count == 5); // List fRetValue + t1 + 3 appends

        list.clear();
        obj = ListTester::getCounter();
        assert(obj.count == 2); // List fRetValue + t1
    }
// ANSI_TEST_N == 1
#endif

#if ANSI_TEST_N == 2
// ANSI_TEST_N == 2
#endif

#if ANSI_TEST_N == 3
// ANSI_TEST_N == 3
#endif

#if ANSI_TEST_N == 4
    carla_stdout("NOTICE LICENSE:");
    carla_stdout(carla_get_extended_license_text());
    carla_stdout("");

    carla_stdout("FILETYPES:");
    carla_stdout(carla_get_supported_file_types());
    carla_stdout("");

    carla_engine_init("beh", "bah");
    carla_stdout(carla_get_last_error());

    carla_engine_close();
    carla_stdout(carla_get_last_error());

// ANSI_TEST_N == 4
#endif

    return 0;
}

// -----------------------------------------------------------------------
