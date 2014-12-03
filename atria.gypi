{
    'variables': {
        'Atria_files': [
            'src/ableton/variant/Match.hpp'
            'src/ableton/variant/Visitor.hpp'
            'src/ableton/estd/memory.hpp'
            'src/ableton/estd/type_traits.hpp'
            'src/ableton/estd/utility.hpp'
            'src/ableton/funken/Commit.hpp'
            'src/ableton/funken/Concepts.hpp'
            'src/ableton/funken/detail/Access.hpp'
            'src/ableton/funken/detail/NoValue.hpp'
            'src/ableton/funken/detail/RootSignals.hpp'
            'src/ableton/funken/detail/Signals.hpp'
            'src/ableton/funken/detail/Watchable.hpp'
            'src/ableton/funken/detail/XformSignals.hpp'
            'src/ableton/funken/In.hpp'
            'src/ableton/funken/Inout.hpp'
            'src/ableton/funken/Out.hpp'
            'src/ableton/funken/Sensor.hpp'
            'src/ableton/funken/State.hpp'
            'src/ableton/funken/Struct.hpp'
            'src/ableton/funken/Watch.hpp'
            'src/ableton/funken/Xformed.hpp'
            'src/ableton/meta/CommonType.hpp'
            'src/ableton/meta/Concept.hpp'
            'src/ableton/meta/Pack.hpp'
            'src/ableton/meta/StdTuple.hpp'
            'src/ableton/meta/Utils.hpp'
            'src/ableton/testing/Benchmark.hpp'
            'src/ableton/testing/Spies.hpp'
            'src/ableton/xform/Functional.hpp'
            'src/ableton/xform/Reduce.hpp'
            'src/ableton/xform/Transducers.hpp'
            'src/ableton/testing/Spies.hpp',
            'src/ableton/testing/Benchmark.hpp',
        ],

        'AtriaTest_files': [
            'src/ableton/variant/tst_Match.cpp',
            'src/ableton/funken/tst_InAndOut.cpp',
            'src/ableton/funken/tst_Sensor.cpp',
            'src/ableton/funken/tst_State.cpp',
            'src/ableton/funken/tst_Struct.cpp',
            'src/ableton/funken/tst_Xformed.cpp',
            'src/ableton/xform/tst_Transducers.cpp',
            'src/ableton/xform/tst_Transducers_Benchmark.cpp',
            'src/ableton/meta/tst_Concepts.cpp',
            'src/ableton/meta/tst_Pack.cpp',
            'src/ableton/meta/tst_StdTuple.cpp',
            'src/ableton/testing/tst_Spies.cpp',
            'src/ableton/testing/tst_Benchmark.cpp'
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
