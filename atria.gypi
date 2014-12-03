{
    'variables': {
        'Atria_files': [
            'src/atria/variant/Match.hpp'
            'src/atria/variant/Visitor.hpp'
            'src/atria/estd/memory.hpp'
            'src/atria/estd/type_traits.hpp'
            'src/atria/estd/utility.hpp'
            'src/atria/funken/Commit.hpp'
            'src/atria/funken/Concepts.hpp'
            'src/atria/funken/detail/Access.hpp'
            'src/atria/funken/detail/NoValue.hpp'
            'src/atria/funken/detail/RootSignals.hpp'
            'src/atria/funken/detail/Signals.hpp'
            'src/atria/funken/detail/Watchable.hpp'
            'src/atria/funken/detail/XformSignals.hpp'
            'src/atria/funken/In.hpp'
            'src/atria/funken/Inout.hpp'
            'src/atria/funken/Out.hpp'
            'src/atria/funken/Sensor.hpp'
            'src/atria/funken/State.hpp'
            'src/atria/funken/Struct.hpp'
            'src/atria/funken/Watch.hpp'
            'src/atria/funken/Xformed.hpp'
            'src/atria/meta/CommonType.hpp'
            'src/atria/meta/Concept.hpp'
            'src/atria/meta/Pack.hpp'
            'src/atria/meta/StdTuple.hpp'
            'src/atria/meta/Utils.hpp'
            'src/atria/testing/Benchmark.hpp'
            'src/atria/testing/Spies.hpp'
            'src/atria/xform/Functional.hpp'
            'src/atria/xform/Reduce.hpp'
            'src/atria/xform/Transducers.hpp'
            'src/atria/testing/Spies.hpp',
            'src/atria/testing/Benchmark.hpp',
        ],

        'AtriaTest_files': [
            'src/atria/variant/tst_Match.cpp',
            'src/atria/funken/tst_InAndOut.cpp',
            'src/atria/funken/tst_Sensor.cpp',
            'src/atria/funken/tst_State.cpp',
            'src/atria/funken/tst_Struct.cpp',
            'src/atria/funken/tst_Xformed.cpp',
            'src/atria/xform/tst_Transducers.cpp',
            'src/atria/xform/tst_Transducers_Benchmark.cpp',
            'src/atria/meta/tst_Concepts.cpp',
            'src/atria/meta/tst_Pack.cpp',
            'src/atria/meta/tst_StdTuple.cpp',
            'src/atria/testing/tst_Spies.cpp',
            'src/atria/testing/tst_Benchmark.cpp'
        ],

        'AtriaSrc_dir': 'src',
        'AtriaInclude_dir': '<(AtriaSrc_dir)'
    },

    'targets': [
        {
            'target_name': 'Atria',
            'type': '<(LibraryType)',

            'include_dirs': [
                '<@(AtriaInclude_dir)',
            ],

            'dependencies': [
                'XBoostLibCommons'
            ],

            'sources': [
                '<@(Atria_files)',
            ],
        },
        {
            'target_name': 'AtriaTest',
            'type': 'executable',

            'include_dirs': [
                '<@(AtriaInclude_dir)',
            ],

            'dependencies': [
                'XGoogleTest',
                'Atria',
            ],

            'sources': [
                '<@(AtriaTest_files)',
            ],
        },
    ],
}
