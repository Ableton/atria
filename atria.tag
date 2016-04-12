<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>functional.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/estd/</path>
    <filename>functional_8hpp</filename>
    <namespace>atria</namespace>
    <namespace>atria::estd</namespace>
  </compound>
  <compound kind="file">
    <name>memory.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/estd/</path>
    <filename>memory_8hpp</filename>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::estd</namespace>
  </compound>
  <compound kind="file">
    <name>string.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/estd/</path>
    <filename>string_8hpp</filename>
    <namespace>atria</namespace>
    <namespace>atria::estd</namespace>
  </compound>
  <compound kind="file">
    <name>tuple_hash.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/estd/</path>
    <filename>tuple__hash_8hpp</filename>
    <class kind="struct">std::hash&lt; tuple&lt; Ts... &gt; &gt;</class>
  </compound>
  <compound kind="file">
    <name>type_traits.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/estd/</path>
    <filename>type__traits_8hpp</filename>
    <class kind="struct">atria::estd::nonesuch</class>
    <namespace>atria</namespace>
    <namespace>atria::estd</namespace>
    <member kind="typedef">
      <type>typename detail::make_void&lt; Ts... &gt;::type</type>
      <name>void_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>adbf75a4cd9d4bd42ac66686f1125821a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::decay&lt; T &gt;::type</type>
      <name>decay_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>abccbc22bdad41d01de217a42e0d077ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::result_of&lt; T &gt;::type</type>
      <name>result_of_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>abf1c2986a71eebc351b3b2b01cc442e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::conditional&lt; X, T, F &gt;::type</type>
      <name>conditional_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>a7e8ac30440b9ec3fef45a9172f1f43f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::remove_reference&lt; T &gt;::type</type>
      <name>remove_reference_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>a3a08cea569e6926ac8d7d74dd7178b5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::remove_const&lt; T &gt;::type</type>
      <name>remove_const_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>a31ee6e9231fa50c7fdd7292f0c45f13e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::enable_if&lt; X, T &gt;::type</type>
      <name>enable_if_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>a3d7e0f60f8c349b2a05f1fcf56750360</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename detail::detector&lt; nonesuch, void, Op, Args... &gt;::value_t</type>
      <name>is_detected</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>a16a19bd6407910d9725dcd05536f5901</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename detail::detector&lt; nonesuch, void, Op, Args... &gt;::type</type>
      <name>detected_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>aeddaa6436b2284bf4bc0c4620a2ded33</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>detail::detector&lt; Default, void, Op, Args... &gt;</type>
      <name>detected_or</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>a0db8e3a48df40f65b7946b4db63747eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename detected_or&lt; Default, Op, Args... &gt;::type</type>
      <name>detected_or_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>a80f94c5a0b73ffc291247f406ee7e3b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::is_same&lt; Expected, detected_t&lt; Op, Args... &gt; &gt;</type>
      <name>is_detected_exact</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>a54efded7d5471a1b8d88f5c2422a767e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::is_convertible&lt; detected_t&lt; Op, Args... &gt;, To &gt;</type>
      <name>is_detected_convertible</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>ac286f275998780a3a3ce9fe2795db6aa</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>utility.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/estd/</path>
    <filename>utility_8hpp</filename>
    <class kind="struct">atria::estd::integer_sequence</class>
    <namespace>atria</namespace>
    <namespace>atria::estd</namespace>
  </compound>
  <compound kind="file">
    <name>commit.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/funken/</path>
    <filename>commit_8hpp</filename>
    <includes id="access_8hpp" name="access.hpp" local="no" imported="no">atria/funken/detail/access.hpp</includes>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::funken</namespace>
  </compound>
  <compound kind="file">
    <name>concepts.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/funken/</path>
    <filename>funken_2concepts_8hpp</filename>
    <includes id="concept_8hpp" name="concept.hpp" local="no" imported="no">atria/meta/concept.hpp</includes>
    <includes id="value__type_8hpp" name="value_type.hpp" local="no" imported="no">atria/meta/value_type.hpp</includes>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::funken</namespace>
    <member kind="function">
      <type></type>
      <name>ABL_CONCEPT_SPEC</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a1397595b0f7785bf65ba657255da83fc</anchor>
      <arglist>(In_value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ABL_CONCEPT_SPEC</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a5303cbcb73a924b458ee098e3ee860c9</anchor>
      <arglist>(Out_value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ABL_CONCEPT_SPEC</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>af84b9510943cdbf07d6ecb038961df9c</anchor>
      <arglist>(Inout_value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ABL_CONCEPT_SPEC</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a30cbff4de15a4a6c2904097da49d7a69</anchor>
      <arglist>(Root_value)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>concepts.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>xform_2concepts_8hpp</filename>
    <includes id="constantly_8hpp" name="constantly.hpp" local="no" imported="no">atria/prelude/constantly.hpp</includes>
    <includes id="concept_8hpp" name="concept.hpp" local="no" imported="no">atria/meta/concept.hpp</includes>
    <includes id="state__traits_8hpp" name="state_traits.hpp" local="no" imported="no">atria/xform/state_traits.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type></type>
      <name>ABL_CONCEPT_SPEC</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a6f09f6f468f00951f63d476cf3f200a2</anchor>
      <arglist>(State)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ABL_CONCEPT_SPEC</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a5d61103acf5e43b32458b61b4fb5c42f</anchor>
      <arglist>(Reducing_function)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ABL_CONCEPT_SPEC</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a80625416b5ebf0ce957cd1fd296ed80c</anchor>
      <arglist>(Transducer)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ABL_CONCEPT_SPEC</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ae50c949c55e49a934999f8724e805309</anchor>
      <arglist>(Transparent_transducer)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>access.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/funken/detail/</path>
    <filename>access_8hpp</filename>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::funken</namespace>
  </compound>
  <compound kind="file">
    <name>no_value.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/funken/detail/</path>
    <filename>no__value_8hpp</filename>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <class kind="struct">atria::funken::no_value_error</class>
    <namespace>atria</namespace>
    <namespace>atria::funken</namespace>
  </compound>
  <compound kind="file">
    <name>root_signals.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/funken/detail/</path>
    <filename>root__signals_8hpp</filename>
    <includes id="signals_8hpp" name="signals.hpp" local="no" imported="no">atria/funken/detail/signals.hpp</includes>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::funken</namespace>
  </compound>
  <compound kind="file">
    <name>signals.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/funken/detail/</path>
    <filename>signals_8hpp</filename>
    <namespace>atria</namespace>
    <namespace>atria::funken</namespace>
  </compound>
  <compound kind="file">
    <name>watchable.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/funken/detail/</path>
    <filename>watchable_8hpp</filename>
    <namespace>atria</namespace>
    <namespace>atria::funken</namespace>
  </compound>
  <compound kind="file">
    <name>xform_signals.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/funken/detail/</path>
    <filename>xform__signals_8hpp</filename>
    <includes id="signals_8hpp" name="signals.hpp" local="no" imported="no">atria/funken/detail/signals.hpp</includes>
    <includes id="no__value_8hpp" name="no_value.hpp" local="no" imported="no">atria/funken/detail/no_value.hpp</includes>
    <includes id="pack_8hpp" name="pack.hpp" local="no" imported="no">atria/meta/pack.hpp</includes>
    <includes id="value__type_8hpp" name="value_type.hpp" local="no" imported="no">atria/meta/value_type.hpp</includes>
    <includes id="identity_8hpp" name="identity.hpp" local="no" imported="no">atria/prelude/identity.hpp</includes>
    <includes id="tuplify_8hpp" name="tuplify.hpp" local="no" imported="no">atria/prelude/tuplify.hpp</includes>
    <includes id="meta_8hpp" name="meta.hpp" local="no" imported="no">atria/xform/meta.hpp</includes>
    <includes id="last__rf_8hpp" name="last_rf.hpp" local="no" imported="no">atria/xform/reducing/last_rf.hpp</includes>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="utility_8hpp" name="utility.hpp" local="no" imported="no">atria/estd/utility.hpp</includes>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::funken</namespace>
  </compound>
  <compound kind="file">
    <name>in.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/funken/</path>
    <filename>in_8hpp</filename>
    <includes id="signals_8hpp" name="signals.hpp" local="no" imported="no">atria/funken/detail/signals.hpp</includes>
    <includes id="access_8hpp" name="access.hpp" local="no" imported="no">atria/funken/detail/access.hpp</includes>
    <includes id="watchable_8hpp" name="watchable.hpp" local="no" imported="no">atria/funken/detail/watchable.hpp</includes>
    <includes id="funken_2concepts_8hpp" name="concepts.hpp" local="no" imported="no">atria/funken/concepts.hpp</includes>
    <class kind="class">atria::funken::input</class>
    <namespace>atria</namespace>
    <namespace>atria::funken</namespace>
    <member kind="function">
      <type>auto</type>
      <name>in</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>ae31a5ffbac61510c6080d6b4c3bc753d</anchor>
      <arglist>(InT &amp;&amp;object) -&gt; estd::enable_if_t&lt;              (In_value&lt; InT &gt;()),           detail::input_impl&lt; detail::signal_type_t&lt; InT &gt; &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>inout.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/funken/</path>
    <filename>inout_8hpp</filename>
    <includes id="signals_8hpp" name="signals.hpp" local="no" imported="no">atria/funken/detail/signals.hpp</includes>
    <includes id="access_8hpp" name="access.hpp" local="no" imported="no">atria/funken/detail/access.hpp</includes>
    <includes id="watchable_8hpp" name="watchable.hpp" local="no" imported="no">atria/funken/detail/watchable.hpp</includes>
    <includes id="funken_2concepts_8hpp" name="concepts.hpp" local="no" imported="no">atria/funken/concepts.hpp</includes>
    <class kind="class">atria::funken::inoutput</class>
    <namespace>atria</namespace>
    <namespace>atria::funken</namespace>
    <member kind="function">
      <type>auto</type>
      <name>inout</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a3d4e799f1a23b57de707a04e33ca193f</anchor>
      <arglist>(InoutT &amp;&amp;object) -&gt; estd::enable_if_t&lt;              (Inout_value&lt; InoutT &gt;()),           detail::inoutput_impl&lt; detail::signal_type_t&lt; InoutT &gt; &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>out.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/funken/</path>
    <filename>out_8hpp</filename>
    <includes id="signals_8hpp" name="signals.hpp" local="no" imported="no">atria/funken/detail/signals.hpp</includes>
    <includes id="access_8hpp" name="access.hpp" local="no" imported="no">atria/funken/detail/access.hpp</includes>
    <includes id="watchable_8hpp" name="watchable.hpp" local="no" imported="no">atria/funken/detail/watchable.hpp</includes>
    <includes id="funken_2concepts_8hpp" name="concepts.hpp" local="no" imported="no">atria/funken/concepts.hpp</includes>
    <class kind="class">atria::funken::output</class>
    <namespace>atria</namespace>
    <namespace>atria::funken</namespace>
    <member kind="function">
      <type>auto</type>
      <name>out</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a8fa6c1b4a04d300807da8ba38beb175e</anchor>
      <arglist>(OutT &amp;&amp;object) -&gt; estd::enable_if_t&lt;              (Out_value&lt; OutT &gt;()),           detail::output_impl&lt; detail::signal_type_t&lt; OutT &gt; &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>sensor.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/funken/</path>
    <filename>sensor_8hpp</filename>
    <includes id="root__signals_8hpp" name="root_signals.hpp" local="no" imported="no">atria/funken/detail/root_signals.hpp</includes>
    <includes id="access_8hpp" name="access.hpp" local="no" imported="no">atria/funken/detail/access.hpp</includes>
    <includes id="watchable_8hpp" name="watchable.hpp" local="no" imported="no">atria/funken/detail/watchable.hpp</includes>
    <class kind="class">atria::funken::sensor</class>
    <namespace>atria</namespace>
    <namespace>atria::funken</namespace>
  </compound>
  <compound kind="file">
    <name>state.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/funken/</path>
    <filename>state_8hpp</filename>
    <includes id="root__signals_8hpp" name="root_signals.hpp" local="no" imported="no">atria/funken/detail/root_signals.hpp</includes>
    <includes id="access_8hpp" name="access.hpp" local="no" imported="no">atria/funken/detail/access.hpp</includes>
    <includes id="watchable_8hpp" name="watchable.hpp" local="no" imported="no">atria/funken/detail/watchable.hpp</includes>
    <class kind="class">atria::funken::state</class>
    <namespace>atria</namespace>
    <namespace>atria::funken</namespace>
  </compound>
  <compound kind="file">
    <name>structure.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/funken/</path>
    <filename>structure_8hpp</filename>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <class kind="struct">atria::funken::structure</class>
    <class kind="struct">std::hash&lt; atria::funken::structure&lt; T &gt; &gt;</class>
    <namespace>atria</namespace>
    <namespace>atria::funken</namespace>
    <member kind="function">
      <type>auto</type>
      <name>modified</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a33481a7baa80556faa4670ea386ea5a7</anchor>
      <arglist>(T &amp;) -&gt; estd::enable_if_t&lt;!std::is_convertible&lt; T &amp;, structure&lt; T &gt; &amp; &gt;::value &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>watch.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/funken/</path>
    <filename>watch_8hpp</filename>
    <includes id="access_8hpp" name="access.hpp" local="no" imported="no">atria/funken/detail/access.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::funken</namespace>
  </compound>
  <compound kind="file">
    <name>xformed.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/funken/</path>
    <filename>xformed_8hpp</filename>
    <includes id="in_8hpp" name="in.hpp" local="no" imported="no">atria/funken/in.hpp</includes>
    <includes id="inout_8hpp" name="inout.hpp" local="no" imported="no">atria/funken/inout.hpp</includes>
    <includes id="xform__signals_8hpp" name="xform_signals.hpp" local="no" imported="no">atria/funken/detail/xform_signals.hpp</includes>
    <includes id="map_8hpp" name="map.hpp" local="no" imported="no">atria/xform/transducer/map.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::funken</namespace>
    <member kind="function">
      <type>auto</type>
      <name>xformed</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>ae40b89f6247ee361fd7ba4265f70df72</anchor>
      <arglist>(Xform &amp;&amp;xform, InTs &amp;&amp;...ins) -&gt; estd::enable_if_t&lt;              meta::all(In_value&lt; InTs &gt;()...),           detail::xformed_input&lt;                      typename decltype(                           detail::make_xform_down_signal(                                   xform, detail::access::signal(ins)...)                           )::element_type                   &gt;           &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>xat</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a07d46d69e56e39495628078c7a334b83</anchor>
      <arglist>(KeyT &amp;&amp;key) -&gt; xform::transducer_impl&lt; detail::at_rf_gen, estd::decay_t&lt; KeyT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>uat</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a8ebd860c57ce91e0aa60a0f1eb28b1d0</anchor>
      <arglist>(KeyT &amp;&amp;key) -&gt; detail::at_updater&lt; estd::decay_t&lt; KeyT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>atted</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>afed87db53d811270ec18f3d92b769e9c</anchor>
      <arglist>(KeyT &amp;&amp;k, Ins &amp;&amp;...ins) -&gt; estd::enable_if_t&lt;              meta::all(In_value&lt; Ins &gt;()&amp;&amp;!Out_value&lt; Ins &gt;()...),           decltype(xformed(xat(k), ins...))           &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>get_attr</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a90dd7256b896c1025a5fa9c555f1213e</anchor>
      <arglist>(AttrPtrT p) -&gt; detail::get_attr_fn&lt; AttrPtrT &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>set_attr</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a147be8a16f2874a61045fd9a6da63af1</anchor>
      <arglist>(AttrPtrT p) -&gt; detail::set_attr_fn&lt; AttrPtrT &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>attred</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>aba2e0bc257a375e095eb096264dc5335</anchor>
      <arglist>(AttrPtrT attr, Ins &amp;&amp;...ins) -&gt; estd::enable_if_t&lt;              meta::all(In_value&lt; Ins &gt;()&amp;&amp;!Out_value&lt; Ins &gt;()...),                                   decltype(xformed(xform::map(get_attr(attr)), ins...))           &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>common_type.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/meta/</path>
    <filename>common__type_8hpp</filename>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <includes id="pack_8hpp" name="pack.hpp" local="no" imported="no">atria/meta/pack.hpp</includes>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <class kind="struct">atria::meta::could_not_find_common_type</class>
    <class kind="struct">atria::meta::common_type</class>
    <class kind="struct">atria::meta::common_type&lt; T, Ts... &gt;</class>
    <class kind="struct">atria::meta::common_type&lt;&gt;</class>
    <namespace>atria</namespace>
    <namespace>atria::meta</namespace>
    <member kind="typedef">
      <type>typename common_type&lt; Ts... &gt;::type</type>
      <name>common_type_t</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>aba0e22763ba45cf3edf22f604e5ed3ae</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>concept.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/meta/</path>
    <filename>concept_8hpp</filename>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <includes id="pack_8hpp" name="pack.hpp" local="no" imported="no">atria/meta/pack.hpp</includes>
    <class kind="struct">atria::meta::models</class>
    <class kind="struct">atria::meta::models&lt;                  ConceptSpecT(Ts...),           estd::void_t&lt;                                                  decltype(std::declval&lt; ConceptSpecT &gt;().requires_(                                                                                                                                   std::declval&lt; Ts &gt;()...))                           &gt;           &gt;</class>
    <class kind="struct">atria::meta::models_</class>
    <class kind="struct">atria::meta::if_any</class>
    <class kind="struct">atria::meta::if_any&lt; T, Mf, Mfs... &gt;</class>
    <class kind="struct">atria::meta::if_any&lt; T, Mf &gt;</class>
    <namespace>atria</namespace>
    <namespace>atria::meta</namespace>
    <member kind="define">
      <type>#define</type>
      <name>ABL_CONCEPT</name>
      <anchorfile>concept_8hpp.html</anchorfile>
      <anchor>a12330bf65f9908ddd814263e1d24d82c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ABL_CONCEPT_SPEC</name>
      <anchorfile>concept_8hpp.html</anchorfile>
      <anchor>aa206482503ade95a039143c176ab5e6a</anchor>
      <arglist>(concept_name)                                                                </arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ABL_ASSERT_CONCEPT</name>
      <anchorfile>concept_8hpp.html</anchorfile>
      <anchor>a94281d994cd7249023beaa06eb3984aa</anchor>
      <arglist>(concept,...)                      </arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ABL_ASSERT_NOT_CONCEPT</name>
      <anchorfile>concept_8hpp.html</anchorfile>
      <anchor>a28063d68d9fee3b9570d4be45645ecbc</anchor>
      <arglist>(concept,...)                      </arglist>
    </member>
    <member kind="typedef">
      <type>estd::enable_if_t&lt; Requirement, int &gt;</type>
      <name>require</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>acecee0f2f55cb61c7c134944be4d7df1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>estd::enable_if_t&lt; if_any&lt; T, Mfs... &gt;::type::value, int &gt;</type>
      <name>require_any</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>af13ec4b3c9557f037c62921d71fbbfeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>all</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>aa4981af4f6de6abc3ecf131454b9e1fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>valid</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>a9e425a1c7a59fc570b8968a2a975c006</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>expressions</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>a15afd0609516e21f990bbcc5b4f69708</anchor>
      <arglist>(Ts &amp;&amp;...)</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>check</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>adf7033d67a82ad70d515d189a054fe2f</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>copy_traits.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/meta/</path>
    <filename>copy__traits_8hpp</filename>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <includes id="eval_8hpp" name="eval.hpp" local="no" imported="no">atria/meta/eval.hpp</includes>
    <class kind="struct">atria::meta::copy_trait</class>
    <class kind="struct">atria::meta::copy_cv</class>
    <class kind="struct">atria::meta::copy_reference</class>
    <class kind="struct">atria::meta::copy_decay</class>
    <namespace>atria</namespace>
    <namespace>atria::meta</namespace>
  </compound>
  <compound kind="file">
    <name>eval.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/meta/</path>
    <filename>eval_8hpp</filename>
    <namespace>atria</namespace>
    <namespace>atria::meta</namespace>
    <member kind="define">
      <type>#define</type>
      <name>ABL_METAFUNCTION_T</name>
      <anchorfile>eval_8hpp.html</anchorfile>
      <anchor>ad594d05aee48ebdf954478613f3834be</anchor>
      <arglist>(name__)                                                        </arglist>
    </member>
    <member kind="typedef">
      <type>typename T::type</type>
      <name>eval_t</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>a077a87021cba858ea8d36b0e1d59f902</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>get_index_sequence.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/meta/</path>
    <filename>get__index__sequence_8hpp</filename>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <includes id="utility_8hpp" name="utility.hpp" local="no" imported="no">atria/estd/utility.hpp</includes>
    <class kind="struct">atria::meta::could_not_get_index_sequence</class>
    <namespace>atria</namespace>
    <namespace>atria::meta</namespace>
  </compound>
  <compound kind="file">
    <name>lazy_enable_if.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/meta/</path>
    <filename>lazy__enable__if_8hpp</filename>
    <includes id="eval_8hpp" name="eval.hpp" local="no" imported="no">atria/meta/eval.hpp</includes>
    <class kind="struct">atria::meta::lazy_enable_if</class>
    <namespace>atria</namespace>
    <namespace>atria::meta</namespace>
  </compound>
  <compound kind="file">
    <name>pack.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/meta/</path>
    <filename>pack_8hpp</filename>
    <class kind="struct">atria::meta::pack</class>
    <class kind="struct">atria::meta::pack_iterator</class>
    <class kind="struct">atria::meta::pack_iterator&lt; atria::meta::pack&lt; Args... &gt; &gt;</class>
    <class kind="struct">boost::mpl::sequence_tag&lt; atria::meta::pack&lt; Args... &gt; &gt;</class>
    <class kind="struct">boost::mpl::front_impl&lt; atria::meta::pack_tag &gt;</class>
    <class kind="struct">boost::mpl::front_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::front_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; T, Ts... &gt; &gt;</class>
    <class kind="struct">boost::mpl::empty_impl&lt; atria::meta::pack_tag &gt;</class>
    <class kind="struct">boost::mpl::empty_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::empty_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; Ts... &gt; &gt;</class>
    <class kind="struct">boost::mpl::pop_front_impl&lt; atria::meta::pack_tag &gt;</class>
    <class kind="struct">boost::mpl::pop_front_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::pop_front_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; First, Types... &gt; &gt;</class>
    <class kind="struct">boost::mpl::push_front_impl&lt; atria::meta::pack_tag &gt;</class>
    <class kind="struct">boost::mpl::push_front_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::push_front_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; Args... &gt;, T &gt;</class>
    <class kind="struct">boost::mpl::push_back_impl&lt; atria::meta::pack_tag &gt;</class>
    <class kind="struct">boost::mpl::push_back_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::push_back_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; Args... &gt;, T &gt;</class>
    <class kind="struct">boost::mpl::size_impl&lt; atria::meta::pack_tag &gt;</class>
    <class kind="struct">boost::mpl::size_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::size_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; Ts... &gt; &gt;</class>
    <class kind="struct">boost::mpl::at_impl&lt; atria::meta::pack_tag &gt;</class>
    <class kind="struct">boost::mpl::at_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::back_impl&lt; atria::meta::pack_tag &gt;</class>
    <class kind="struct">boost::mpl::back_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::clear_impl&lt; atria::meta::pack_tag &gt;</class>
    <class kind="struct">boost::mpl::clear_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::pop_back_impl&lt; atria::meta::pack_tag &gt;</class>
    <class kind="struct">boost::mpl::pop_back_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::begin_impl&lt; atria::meta::pack_tag &gt;</class>
    <class kind="struct">boost::mpl::begin_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::end_impl&lt; atria::meta::pack_tag &gt;</class>
    <class kind="struct">boost::mpl::end_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::deref&lt; atria::meta::pack_iterator&lt;  atria::meta::pack&lt; First, Args... &gt; &gt; &gt;</class>
    <class kind="struct">boost::mpl::next&lt; atria::meta::pack_iterator&lt;  atria::meta::pack&lt; First, Args... &gt; &gt; &gt;</class>
    <namespace>atria</namespace>
    <namespace>atria::meta</namespace>
    <member kind="typedef">
      <type>typename detail::unpack&lt; MF, T &gt;::type</type>
      <name>unpack</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>a11375eeae94b43372dd0f70a867f200f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>operator==</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>afed7f8e3e576f161e31bc472440ee98d</anchor>
      <arglist>(const pack&lt; Ts1... &gt; &amp;, const pack&lt; Ts2... &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>operator!=</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>a944e22221a11965e834bb5ca7116d988</anchor>
      <arglist>(const pack&lt; Ts1... &gt; &amp;, const pack&lt; Ts2... &gt; &amp;)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>std_tuple.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/meta/</path>
    <filename>std__tuple_8hpp</filename>
    <class kind="struct">atria::meta::std_tuple_iterator</class>
    <class kind="struct">atria::meta::std_tuple_iterator&lt; std::tuple&lt; Args... &gt; &gt;</class>
    <class kind="struct">boost::mpl::sequence_tag&lt; std::tuple&lt; Args... &gt; &gt;</class>
    <class kind="struct">boost::mpl::front_impl&lt; atria::meta::std_tuple_tag &gt;</class>
    <class kind="struct">boost::mpl::front_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::empty_impl&lt; atria::meta::std_tuple_tag &gt;</class>
    <class kind="struct">boost::mpl::empty_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::pop_front_impl&lt; atria::meta::std_tuple_tag &gt;</class>
    <class kind="struct">boost::mpl::pop_front_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::pop_front_impl&lt; atria::meta::std_tuple_tag &gt;::apply&lt; std::tuple&lt; First, Types... &gt; &gt;</class>
    <class kind="struct">boost::mpl::push_front_impl&lt; atria::meta::std_tuple_tag &gt;</class>
    <class kind="struct">boost::mpl::push_front_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::push_front_impl&lt; atria::meta::std_tuple_tag &gt;::apply&lt; std::tuple&lt; Args... &gt;, T &gt;</class>
    <class kind="struct">boost::mpl::push_back_impl&lt; atria::meta::std_tuple_tag &gt;</class>
    <class kind="struct">boost::mpl::push_back_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::push_back_impl&lt; atria::meta::std_tuple_tag &gt;::apply&lt; std::tuple&lt; Args... &gt;, T &gt;</class>
    <class kind="struct">boost::mpl::size_impl&lt; atria::meta::std_tuple_tag &gt;</class>
    <class kind="struct">boost::mpl::size_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::at_impl&lt; atria::meta::std_tuple_tag &gt;</class>
    <class kind="struct">boost::mpl::at_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::back_impl&lt; atria::meta::std_tuple_tag &gt;</class>
    <class kind="struct">boost::mpl::back_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::clear_impl&lt; atria::meta::std_tuple_tag &gt;</class>
    <class kind="struct">boost::mpl::clear_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;</class>
    <class kind="struct">boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::tuple_seq</class>
    <class kind="struct">boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::tuple_gens</class>
    <class kind="struct">boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::tuple_gens&lt; 0, S... &gt;</class>
    <class kind="struct">boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::apply_impl</class>
    <class kind="struct">boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::apply_impl&lt; Tuple, tuple_seq&lt; S... &gt; &gt;</class>
    <class kind="struct">boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::begin_impl&lt; atria::meta::std_tuple_tag &gt;</class>
    <class kind="struct">boost::mpl::begin_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::end_impl&lt; atria::meta::std_tuple_tag &gt;</class>
    <class kind="struct">boost::mpl::end_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::deref&lt; atria::meta::std_tuple_iterator&lt; std::tuple&lt; First, Args... &gt; &gt; &gt;</class>
    <class kind="struct">boost::mpl::next&lt; atria::meta::std_tuple_iterator&lt; std::tuple&lt; First, Args... &gt; &gt; &gt;</class>
    <namespace>atria</namespace>
    <namespace>atria::meta</namespace>
  </compound>
  <compound kind="file">
    <name>utils.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/meta/</path>
    <filename>utils_8hpp</filename>
    <class kind="struct">atria::meta::identity</class>
    <class kind="struct">atria::meta::bottom</class>
    <class kind="struct">atria::meta::from_void</class>
    <class kind="struct">atria::meta::noop_t</class>
    <namespace>atria</namespace>
    <namespace>atria::meta</namespace>
    <member kind="define">
      <type>#define</type>
      <name>ABL_DECLTYPE_RETURN</name>
      <anchorfile>utils_8hpp.html</anchorfile>
      <anchor>accee07a5d877fc2ed91dd358dfd2c222</anchor>
      <arglist>(body_expr)</arglist>
    </member>
    <member kind="variable">
      <type>constexpr int</type>
      <name>can_be_void</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>a3ea3b7864ce402cf4a3060ccea7502f3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>value_type.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/meta/</path>
    <filename>value__type_8hpp</filename>
    <class kind="struct">atria::meta::get_value_type</class>
    <namespace>atria</namespace>
    <namespace>atria::meta</namespace>
    <member kind="typedef">
      <type>eval_t&lt; get_value_type&lt; estd::decay_t&lt; T &gt; &gt; &gt;</type>
      <name>value_t</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>a5dcf93ca18529def3acf809f9e15c67f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>comp.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/prelude/</path>
    <filename>comp_8hpp</filename>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <includes id="functional_8hpp" name="functional.hpp" local="no" imported="no">atria/estd/functional.hpp</includes>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::prelude</namespace>
    <member kind="function">
      <type>auto</type>
      <name>comp</name>
      <anchorfile>namespaceatria_1_1prelude.html</anchorfile>
      <anchor>a76571986e0dbf8a149a1ae55ede5bfde</anchor>
      <arglist>(F &amp;&amp;f) -&gt; F &amp;&amp;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>complement.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/prelude/</path>
    <filename>complement_8hpp</filename>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <includes id="functional_8hpp" name="functional.hpp" local="no" imported="no">atria/estd/functional.hpp</includes>
    <class kind="struct">atria::prelude::complement_t</class>
    <namespace>atria</namespace>
    <namespace>atria::prelude</namespace>
    <member kind="function">
      <type>auto</type>
      <name>complement</name>
      <anchorfile>namespaceatria_1_1prelude.html</anchorfile>
      <anchor>a7458009df9fab4d7899bbda48dd9713d</anchor>
      <arglist>(FnT &amp;&amp;fn) -&gt; complement_t&lt; estd::decay_t&lt; FnT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>constantly.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/prelude/</path>
    <filename>constantly_8hpp</filename>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <class kind="struct">atria::prelude::constantly_t</class>
    <namespace>atria</namespace>
    <namespace>atria::prelude</namespace>
    <member kind="function">
      <type>auto</type>
      <name>constantly</name>
      <anchorfile>namespaceatria_1_1prelude.html</anchorfile>
      <anchor>ae84f7a055fedf797752abfb80f34ae90</anchor>
      <arglist>(T &amp;&amp;value) -&gt; constantly_t&lt; estd::decay_t&lt; T &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>identity.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/prelude/</path>
    <filename>identity_8hpp</filename>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <class kind="struct">atria::prelude::identity_t</class>
    <class kind="struct">atria::prelude::identity_t_</class>
    <namespace>atria</namespace>
    <namespace>atria::prelude</namespace>
  </compound>
  <compound kind="file">
    <name>trace.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/prelude/</path>
    <filename>trace_8hpp</filename>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <class kind="struct">atria::prelude::tracer</class>
    <namespace>atria</namespace>
    <namespace>atria::prelude</namespace>
    <member kind="function">
      <type>auto</type>
      <name>trace</name>
      <anchorfile>namespaceatria_1_1prelude.html</anchorfile>
      <anchor>a727c15b2eda2a38e3a7f526349950c22</anchor>
      <arglist>(T &amp;&amp;x, const std::string &amp;message) -&gt; T &amp;&amp;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tuplify.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/prelude/</path>
    <filename>tuplify_8hpp</filename>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <class kind="struct">atria::prelude::tuplify_t</class>
    <namespace>atria</namespace>
    <namespace>atria::prelude</namespace>
  </compound>
  <compound kind="file">
    <name>benchmark.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/testing/</path>
    <filename>benchmark_8hpp</filename>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <class kind="struct">atria::testing::benchmark_settings</class>
    <class kind="class">atria::testing::benchmark_suite</class>
    <class kind="class">atria::testing::benchmark_suite&lt; void &gt;</class>
    <class kind="struct">atria::testing::benchmark_runner_error</class>
    <class kind="class">atria::testing::benchmark_runner</class>
    <namespace>atria</namespace>
    <namespace>atria::testing</namespace>
    <member kind="define">
      <type>#define</type>
      <name>ABL_BENCHMARK_MAIN</name>
      <anchorfile>benchmark_8hpp.html</anchorfile>
      <anchor>a724e4698b2bfbf1f07d692c54107f3a5</anchor>
      <arglist>(fn)                                                                </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unoptimize</name>
      <anchorfile>namespaceatria_1_1testing.html</anchorfile>
      <anchor>acd42111d8fcc94dd7fad31a3af055fa7</anchor>
      <arglist>(const void *)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>timeit</name>
      <anchorfile>namespaceatria_1_1testing.html</anchorfile>
      <anchor>a10ed11e83a2e5e54e8eb4b7b003b11d8</anchor>
      <arglist>(FnT &amp;&amp;fn) -&gt; std::chrono::duration&lt; double, std::milli &gt;</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>benchmark_main</name>
      <anchorfile>namespaceatria_1_1testing.html</anchorfile>
      <anchor>a163ec995e873324e3c8c33396e0e799c</anchor>
      <arglist>(int argc, char const *const *argv, FnT &amp;&amp;fn)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>gtest.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/testing/</path>
    <filename>gtest_8hpp</filename>
  </compound>
  <compound kind="file">
    <name>spies.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/testing/</path>
    <filename>spies_8hpp</filename>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <class kind="class">atria::testing::variant_spy</class>
    <class kind="struct">atria::testing::variant_spy::all_variants</class>
    <class kind="struct">atria::testing::mocks::defaulting</class>
    <class kind="struct">atria::testing::mocks::returning</class>
    <class kind="class">atria::testing::spy_fn</class>
    <class kind="struct">atria::testing::copy_spy</class>
    <namespace>atria</namespace>
    <namespace>atria::testing</namespace>
    <member kind="function">
      <type>auto</type>
      <name>spy</name>
      <anchorfile>namespaceatria_1_1testing.html</anchorfile>
      <anchor>a1d690a15d59c27d0f80b28111e85daff</anchor>
      <arglist>(const Fn &amp;fn) -&gt; spy_fn&lt; Fn &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>spy</name>
      <anchorfile>namespaceatria_1_1testing.html</anchorfile>
      <anchor>a728ac676e31248bae49df08233279457</anchor>
      <arglist>() -&gt; spy_fn&lt;&gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>spy_on</name>
      <anchorfile>namespaceatria_1_1testing.html</anchorfile>
      <anchor>a131ae9a05d71f92e0f898404c74dcbb1</anchor>
      <arglist>(MockT &amp;mock) -&gt; spy_fn&lt; detail::scoped_intruder&lt; MockT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>spy_on</name>
      <anchorfile>namespaceatria_1_1testing.html</anchorfile>
      <anchor>a76b48581275e46d9c3745772a1a148b1</anchor>
      <arglist>(MockT &amp;mock, const FnT &amp;replacement) -&gt; spy_fn&lt; detail::scoped_intruder&lt; MockT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>match_boost.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/variant/</path>
    <filename>match__boost_8hpp</filename>
    <includes id="variant__types__boost_8hpp" name="variant_types_boost.hpp" local="no" imported="no">atria/variant/variant_types_boost.hpp</includes>
    <includes id="visitor_8hpp" name="visitor.hpp" local="no" imported="no">atria/variant/visitor.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::variant</namespace>
    <member kind="function">
      <type>auto</type>
      <name>match</name>
      <anchorfile>namespaceatria_1_1variant.html</anchorfile>
      <anchor>a26f1198672773eafb32564299c7ed575</anchor>
      <arglist>(VariantT &amp;variant, FnTs &amp;&amp;...fns) -&gt; estd::enable_if_t&lt;      detail::is_boost_variant&lt; estd::decay_t&lt; VariantT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>match_eggs.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/variant/</path>
    <filename>match__eggs_8hpp</filename>
    <includes id="variant__types__eggs_8hpp" name="variant_types_eggs.hpp" local="no" imported="no">atria/variant/variant_types_eggs.hpp</includes>
    <includes id="visitor_8hpp" name="visitor.hpp" local="no" imported="no">atria/variant/visitor.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::variant</namespace>
    <member kind="function">
      <type>auto</type>
      <name>match</name>
      <anchorfile>namespaceatria_1_1variant.html</anchorfile>
      <anchor>a805602a61739301616b7a4eca1fd42c0</anchor>
      <arglist>(VariantT &amp;&amp;variant, FnTs &amp;&amp;...fns) -&gt; estd::enable_if_t&lt;      detail::is_eggs_variant&lt; estd::decay_t&lt; VariantT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>variant_types.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/variant/</path>
    <filename>variant__types_8hpp</filename>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <includes id="copy__traits_8hpp" name="copy_traits.hpp" local="no" imported="no">atria/meta/copy_traits.hpp</includes>
    <includes id="pack_8hpp" name="pack.hpp" local="no" imported="no">atria/meta/pack.hpp</includes>
    <class kind="struct">atria::variant::variant_types_impl</class>
    <class kind="struct">atria::variant::variant_types_impl&lt; meta::pack&lt; Ts... &gt; &gt;</class>
    <class kind="struct">atria::variant::variant_types</class>
    <namespace>atria</namespace>
    <namespace>atria::variant</namespace>
  </compound>
  <compound kind="file">
    <name>variant_types_boost.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/variant/</path>
    <filename>variant__types__boost_8hpp</filename>
    <includes id="variant__types_8hpp" name="variant_types.hpp" local="no" imported="no">atria/variant/variant_types.hpp</includes>
    <class kind="struct">atria::variant::variant_types_impl&lt; boost::variant&lt; T, Ts... &gt; &gt;</class>
    <namespace>atria</namespace>
    <namespace>atria::variant</namespace>
  </compound>
  <compound kind="file">
    <name>variant_types_eggs.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/variant/</path>
    <filename>variant__types__eggs_8hpp</filename>
    <includes id="variant__types_8hpp" name="variant_types.hpp" local="no" imported="no">atria/variant/variant_types.hpp</includes>
    <class kind="struct">atria::variant::variant_types_impl&lt; eggs::variants::variant&lt; Ts... &gt; &gt;</class>
    <namespace>atria</namespace>
    <namespace>atria::variant</namespace>
  </compound>
  <compound kind="file">
    <name>visitor.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/variant/</path>
    <filename>visitor_8hpp</filename>
    <includes id="variant__types_8hpp" name="variant_types.hpp" local="no" imported="no">atria/variant/variant_types.hpp</includes>
    <includes id="common__type_8hpp" name="common_type.hpp" local="no" imported="no">atria/meta/common_type.hpp</includes>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <class kind="class">atria::variant::visitor_t</class>
    <class kind="struct">atria::variant::otherwise_t</class>
    <class kind="struct">atria::variant::when_t</class>
    <class kind="struct">atria::variant::visitor_result_of</class>
    <class kind="struct">atria::variant::visitor_result_of&lt; FnT, meta::pack&lt; VariantTs... &gt; &gt;</class>
    <namespace>atria</namespace>
    <namespace>atria::variant</namespace>
    <member kind="function">
      <type>when_t&lt; Fn, typename boost::mpl::if_&lt; std::is_reference&lt; Args &gt;, Args, const Args &amp; &gt;::type... &gt;</type>
      <name>when</name>
      <anchorfile>namespaceatria_1_1variant.html</anchorfile>
      <anchor>ab60ccb4829cc97083de66d8a36bf1bdd</anchor>
      <arglist>(Fn &amp;&amp;fn)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>visitor</name>
      <anchorfile>namespaceatria_1_1variant.html</anchorfile>
      <anchor>a1fd6a365e6153690733db03820dd1984</anchor>
      <arglist>(FnTs &amp;&amp;...fns) -&gt; visitor_t&lt;              meta::common_type_t&lt;                      typename std::result_of&lt; FnTs(meta::bottom)&gt;::type... &gt;,           FnTs... &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>visitor_for</name>
      <anchorfile>namespaceatria_1_1variant.html</anchorfile>
      <anchor>adf7c7bfe6f794ce07243e09c95dd59bb</anchor>
      <arglist>(FnTs &amp;&amp;...fns) -&gt; visitor_t&lt;              visitor_result_of_t&lt;                      detail::visitor_impl&lt; FnTs... &gt;,                   variant_types_t&lt; VariantT &gt; &gt;,           FnTs... &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>any_state.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>any__state_8hpp</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" imported="no">atria/xform/config.hpp</includes>
    <includes id="state__traits_8hpp" name="state_traits.hpp" local="no" imported="no">atria/xform/state_traits.hpp</includes>
    <includes id="memory_8hpp" name="memory.hpp" local="no" imported="no">atria/estd/memory.hpp</includes>
    <includes id="pack_8hpp" name="pack.hpp" local="no" imported="no">atria/meta/pack.hpp</includes>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <class kind="class">atria::xform::any_state</class>
    <class kind="struct">atria::xform::state_traits&lt; any_state &gt;</class>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>config.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>config_8hpp</filename>
    <member kind="define">
      <type>#define</type>
      <name>ABL_STATEFUL_INTO</name>
      <anchorfile>config_8hpp.html</anchorfile>
      <anchor>ad7f8c827973a0635c3cfc2bda3910d21</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ABL_SAFE_ANY_STATE</name>
      <anchorfile>config_8hpp.html</anchorfile>
      <anchor>a03ab68f8fa4bd0a077a4c6b029560cd0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ABL_TRACE_ANY_STATE_ALLOC</name>
      <anchorfile>config_8hpp.html</anchorfile>
      <anchor>a4c64c66950307e489c204e4367232b05</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ABL_REDUCE_TAIL_RECURSIVE</name>
      <anchorfile>config_8hpp.html</anchorfile>
      <anchor>a452660ed8afbb4c736c05ead662960f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ABL_REDUCE_WITH_ACCUMULATE</name>
      <anchorfile>config_8hpp.html</anchorfile>
      <anchor>a84105256ae0ffa5b868ec094bbc0fa57</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ABL_REDUCE_ALWAYS_VARIADIC</name>
      <anchorfile>config_8hpp.html</anchorfile>
      <anchor>afbd6db7d5f53015242a09b4c4d0e4b2b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ABL_MAKE_GCC_CRASH</name>
      <anchorfile>config_8hpp.html</anchorfile>
      <anchor>aeeb223fd9ae35cef72238c38c4293e1c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>empty_transducer_error.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/detail/</path>
    <filename>empty__transducer__error_8hpp</filename>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>is_non_empty.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/detail/</path>
    <filename>is__non__empty_8hpp</filename>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>reduce_nested_non_empty.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/detail/</path>
    <filename>reduce__nested__non__empty_8hpp</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" imported="no">atria/xform/config.hpp</includes>
    <includes id="reduce__nested__non__empty__variadic_8hpp" name="reduce_nested_non_empty_variadic.hpp" local="no" imported="no">atria/xform/detail/reduce_nested_non_empty_variadic.hpp</includes>
    <includes id="reduce__nested__non__empty__nullary_8hpp" name="reduce_nested_non_empty_nullary.hpp" local="no" imported="no">atria/xform/detail/reduce_nested_non_empty_nullary.hpp</includes>
    <includes id="reduce__nested__non__empty__non__variadic_8hpp" name="reduce_nested_non_empty_non_variadic.hpp" local="no" imported="no">atria/xform/detail/reduce_nested_non_empty_non_variadic.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>reduce_nested_non_empty_accumulate.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/detail/</path>
    <filename>reduce__nested__non__empty__accumulate_8hpp</filename>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>reduce_nested_non_empty_non_variadic.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/detail/</path>
    <filename>reduce__nested__non__empty__non__variadic_8hpp</filename>
    <includes id="state__traits_8hpp" name="state_traits.hpp" local="no" imported="no">atria/xform/state_traits.hpp</includes>
    <includes id="copy__traits_8hpp" name="copy_traits.hpp" local="no" imported="no">atria/meta/copy_traits.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>reduce_nested_non_empty_nullary.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/detail/</path>
    <filename>reduce__nested__non__empty__nullary_8hpp</filename>
    <includes id="state__traits_8hpp" name="state_traits.hpp" local="no" imported="no">atria/xform/state_traits.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>reduce_nested_non_empty_tail_recursive.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/detail/</path>
    <filename>reduce__nested__non__empty__tail__recursive_8hpp</filename>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>reduce_nested_non_empty_variadic.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/detail/</path>
    <filename>reduce__nested__non__empty__variadic_8hpp</filename>
    <includes id="tuple__utils_8hpp" name="tuple_utils.hpp" local="no" imported="no">atria/xform/detail/tuple_utils.hpp</includes>
    <includes id="state__traits_8hpp" name="state_traits.hpp" local="no" imported="no">atria/xform/state_traits.hpp</includes>
    <includes id="utility_8hpp" name="utility.hpp" local="no" imported="no">atria/estd/utility.hpp</includes>
    <includes id="copy__traits_8hpp" name="copy_traits.hpp" local="no" imported="no">atria/meta/copy_traits.hpp</includes>
    <includes id="pack_8hpp" name="pack.hpp" local="no" imported="no">atria/meta/pack.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>tuple_utils.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/detail/</path>
    <filename>tuple__utils_8hpp</filename>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>abort_reduce.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/impure/</path>
    <filename>abort__reduce_8hpp</filename>
    <includes id="state__traits_8hpp" name="state_traits.hpp" local="no" imported="no">atria/xform/state_traits.hpp</includes>
    <includes id="utility_8hpp" name="utility.hpp" local="no" imported="no">atria/estd/utility.hpp</includes>
    <class kind="struct">atria::xform::impure::reduce_aborted_error_base</class>
    <class kind="struct">atria::xform::impure::reduce_aborted_error</class>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>into.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/impure/</path>
    <filename>impure_2into_8hpp</filename>
    <includes id="impure_2transduce_8hpp" name="transduce.hpp" local="no" imported="no">atria/xform/impure/transduce.hpp</includes>
    <includes id="output__rf_8hpp" name="output_rf.hpp" local="no" imported="no">atria/xform/reducing/output_rf.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>into.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>into_8hpp</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" imported="no">atria/xform/config.hpp</includes>
    <includes id="transduce_8hpp" name="transduce.hpp" local="no" imported="no">atria/xform/transduce.hpp</includes>
    <includes id="output__rf_8hpp" name="output_rf.hpp" local="no" imported="no">atria/xform/reducing/output_rf.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>into</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a8acde91bb38a74e8111d03f72f991470</anchor>
      <arglist>(CollectionT &amp;&amp;col, XformT &amp;&amp;xform, InputRangeTs &amp;&amp;...ranges) -&gt; CollectionT &amp;&amp;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>reduce.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/impure/</path>
    <filename>impure_2reduce_8hpp</filename>
    <includes id="any__state_8hpp" name="any_state.hpp" local="no" imported="no">atria/xform/any_state.hpp</includes>
    <includes id="abort__reduce_8hpp" name="abort_reduce.hpp" local="no" imported="no">atria/xform/impure/abort_reduce.hpp</includes>
    <includes id="reduce__nested__non__empty_8hpp" name="reduce_nested_non_empty.hpp" local="no" imported="no">atria/xform/detail/reduce_nested_non_empty.hpp</includes>
    <includes id="is__non__empty_8hpp" name="is_non_empty.hpp" local="no" imported="no">atria/xform/detail/is_non_empty.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>reduce.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>reduce_8hpp</filename>
    <includes id="reduce__nested__non__empty_8hpp" name="reduce_nested_non_empty.hpp" local="no" imported="no">atria/xform/detail/reduce_nested_non_empty.hpp</includes>
    <includes id="is__non__empty_8hpp" name="is_non_empty.hpp" local="no" imported="no">atria/xform/detail/is_non_empty.hpp</includes>
    <includes id="state__traits_8hpp" name="state_traits.hpp" local="no" imported="no">atria/xform/state_traits.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>reduce</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a85da5e5fc0bf1b8b7ccf1eaf11b7fd80</anchor>
      <arglist>(ReducingFnT &amp;&amp;step, StateT &amp;&amp;state, InputRangeTs &amp;&amp;...ranges) -&gt; estd::decay_t&lt; StateT &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>transduce.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/impure/</path>
    <filename>impure_2transduce_8hpp</filename>
    <includes id="impure_2reduce_8hpp" name="reduce.hpp" local="no" imported="no">atria/xform/impure/reduce.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>transduce.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>transduce_8hpp</filename>
    <includes id="reduce_8hpp" name="reduce.hpp" local="no" imported="no">atria/xform/reduce.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>transduce</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>aa3ddac4a321b0ab20393f47485e42a50</anchor>
      <arglist>(XformT &amp;&amp;xform, ReducingFnT &amp;&amp;step, StateT &amp;&amp;state, InputRangeTs &amp;&amp;...ranges) -&gt; estd::decay_t&lt; StateT &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>enumerate.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/impure/transducer/</path>
    <filename>impure_2transducer_2enumerate_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>enumerate.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>transducer_2enumerate_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="constantly_8hpp" name="constantly.hpp" local="no" imported="no">atria/prelude/constantly.hpp</includes>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>constexpr auto</type>
      <name>enumerate_from</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a8a075d51b9bc7bda8f0b27de56d38c33</anchor>
      <arglist>(IntegralT &amp;&amp;init) -&gt; enumerate_t&lt; estd::decay_t&lt; IntegralT &gt; &gt;</arglist>
    </member>
    <member kind="variable">
      <type>const enumerate_t&lt; std::size_t &gt;</type>
      <name>enumerate</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a674e6c72a9862bb0968da41dfbcbedef</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>take.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/impure/transducer/</path>
    <filename>impure_2transducer_2take_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>take.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>transducer_2take_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="empty__transducer__error_8hpp" name="empty_transducer_error.hpp" local="no" imported="no">atria/xform/detail/empty_transducer_error.hpp</includes>
    <includes id="constantly_8hpp" name="constantly.hpp" local="no" imported="no">atria/prelude/constantly.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>take</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ad1392e213eac822dbbb8500608012bb4</anchor>
      <arglist>(IntegralT &amp;&amp;n) -&gt; take_t&lt; estd::decay_t&lt; IntegralT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>transducer.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/impure/transducer/</path>
    <filename>impure_2transducer_2transducer_8hpp</filename>
    <includes id="pack_8hpp" name="pack.hpp" local="no" imported="no">atria/meta/pack.hpp</includes>
    <includes id="any__state_8hpp" name="any_state.hpp" local="no" imported="no">atria/xform/any_state.hpp</includes>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="comp_8hpp" name="comp.hpp" local="no" imported="no">atria/prelude/comp.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>transducer.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>transducer_2transducer_8hpp</filename>
    <includes id="pack_8hpp" name="pack.hpp" local="no" imported="no">atria/meta/pack.hpp</includes>
    <includes id="any__state_8hpp" name="any_state.hpp" local="no" imported="no">atria/xform/any_state.hpp</includes>
    <includes id="with__state_8hpp" name="with_state.hpp" local="no" imported="no">atria/xform/with_state.hpp</includes>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="comp_8hpp" name="comp.hpp" local="no" imported="no">atria/prelude/comp.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="typedef">
      <type>transducer_impl&lt; meta::unpack&lt; detail::transducer_rf_gen, OutputT &gt;, detail::transducer_function_t&lt; InputT, OutputT &gt; &gt;</type>
      <name>transducer</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a12e4b8c9b4281bf93d4e649374f2d389</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>into_vector.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>into__vector_8hpp</filename>
    <includes id="into_8hpp" name="into.hpp" local="no" imported="no">atria/xform/into.hpp</includes>
    <includes id="state__traits_8hpp" name="state_traits.hpp" local="no" imported="no">atria/xform/state_traits.hpp</includes>
    <includes id="meta_8hpp" name="meta.hpp" local="no" imported="no">atria/xform/meta.hpp</includes>
    <includes id="last__rf_8hpp" name="last_rf.hpp" local="no" imported="no">atria/xform/reducing/last_rf.hpp</includes>
    <includes id="value__type_8hpp" name="value_type.hpp" local="no" imported="no">atria/meta/value_type.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>into_vector</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ad21b8bf7db847c2dd1ad4e426b938f85</anchor>
      <arglist>(XformT &amp;&amp;xform, InputRangeTs &amp;&amp;...ranges) -&gt; std::vector&lt; result_of_t&lt; XformT, meta::value_t&lt; InputRangeTs &gt;... &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>maybe_reduced.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>maybe__reduced_8hpp</filename>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <class kind="struct">atria::xform::maybe_reduced_tag</class>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="typedef">
      <type>state_wrapper&lt; maybe_reduced_tag, T, bool &gt;</type>
      <name>maybe_reduced</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>af2572203f7496bd93e991b7dbaa2772e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>reduced_if</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a1cdbd85097477b77c5b4e744753e29b8</anchor>
      <arglist>(T &amp;&amp;x, bool is_reduced) -&gt; maybe_reduced&lt; estd::decay_t&lt; T &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>reduced</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a27b1401b1b47815969ff0867ad21f4e5</anchor>
      <arglist>(T &amp;&amp;x) -&gt; decltype(reduced_if(std::forward&lt; T &gt;(x), true))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>not_reduced</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a959ceb0a8362e3e5e4ef9f0a73a163c9</anchor>
      <arglist>(T &amp;&amp;x) -&gt; decltype(reduced_if(std::forward&lt; T &gt;(x), false))</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>meta.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>meta_8hpp</filename>
    <includes id="into_8hpp" name="into.hpp" local="no" imported="no">atria/xform/into.hpp</includes>
    <includes id="state__traits_8hpp" name="state_traits.hpp" local="no" imported="no">atria/xform/state_traits.hpp</includes>
    <includes id="last__rf_8hpp" name="last_rf.hpp" local="no" imported="no">atria/xform/reducing/last_rf.hpp</includes>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <includes id="eval_8hpp" name="eval.hpp" local="no" imported="no">atria/meta/eval.hpp</includes>
    <includes id="pack_8hpp" name="pack.hpp" local="no" imported="no">atria/meta/pack.hpp</includes>
    <class kind="struct">atria::xform::output_of</class>
    <class kind="struct">atria::xform::output_of&lt; XformT, meta::pack&lt; InputTs... &gt; &gt;</class>
    <class kind="struct">atria::xform::result_of</class>
    <class kind="struct">atria::xform::result_of&lt; XformT, meta::pack&lt; InputTs... &gt; &gt;</class>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>reduce_nested.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>reduce__nested_8hpp</filename>
    <includes id="skip_8hpp" name="skip.hpp" local="no" imported="no">atria/xform/skip.hpp</includes>
    <includes id="reduce__nested__non__empty_8hpp" name="reduce_nested_non_empty.hpp" local="no" imported="no">atria/xform/detail/reduce_nested_non_empty.hpp</includes>
    <includes id="is__non__empty_8hpp" name="is_non_empty.hpp" local="no" imported="no">atria/xform/detail/is_non_empty.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>reduce_nested</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>abd7d189e77566f74be8cbad8254ffb5a</anchor>
      <arglist>(ReducingFnT &amp;&amp;step, StateT &amp;&amp;state, InputRangeTs &amp;&amp;...ranges) -&gt; decltype(detail::is_non_empty(ranges...)                   ?call(detail::reduce_nested_non_empty_flipped,                                               std::forward&lt; StateT &gt;(state),                                               std::forward&lt; ReducingFnT &gt;(step),                                               std::forward&lt; InputRangeTs &gt;(ranges)...)                   :skip(std::forward&lt; StateT &gt;(state)))</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>emplace_back_rf.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/reducing/</path>
    <filename>emplace__back__rf_8hpp</filename>
    <includes id="utility_8hpp" name="utility.hpp" local="no" imported="no">atria/estd/utility.hpp</includes>
    <class kind="struct">atria::xform::emplace_back_rf_t</class>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>first_rf.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/reducing/</path>
    <filename>first__rf_8hpp</filename>
    <includes id="utility_8hpp" name="utility.hpp" local="no" imported="no">atria/estd/utility.hpp</includes>
    <class kind="struct">atria::xform::first_rf_t</class>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>last_rf.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/reducing/</path>
    <filename>last__rf_8hpp</filename>
    <includes id="utility_8hpp" name="utility.hpp" local="no" imported="no">atria/estd/utility.hpp</includes>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <includes id="tuplify_8hpp" name="tuplify.hpp" local="no" imported="no">atria/prelude/tuplify.hpp</includes>
    <class kind="struct">atria::xform::last_rf_t</class>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>output_rf.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/reducing/</path>
    <filename>output__rf_8hpp</filename>
    <includes id="utility_8hpp" name="utility.hpp" local="no" imported="no">atria/estd/utility.hpp</includes>
    <includes id="tuplify_8hpp" name="tuplify.hpp" local="no" imported="no">atria/prelude/tuplify.hpp</includes>
    <class kind="struct">atria::xform::output_rf_t</class>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>reductor.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>reductor_8hpp</filename>
    <includes id="skip_8hpp" name="skip.hpp" local="no" imported="no">atria/xform/skip.hpp</includes>
    <includes id="state__traits_8hpp" name="state_traits.hpp" local="no" imported="no">atria/xform/state_traits.hpp</includes>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <class kind="struct">atria::xform::reductor_fn_base</class>
    <class kind="struct">atria::xform::reductor_fn</class>
    <class kind="struct">atria::xform::empty_reductor_fn</class>
    <class kind="struct">atria::xform::empty_reductor_fn&lt; ReducingFnT, InitialStateT, meta::pack&lt; InputTs... &gt; &gt;</class>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>reductor</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a1e39dd603978c9a39ba6eaa5a64369b5</anchor>
      <arglist>(ReducingFnT &amp;&amp;step, InitialStateT &amp;&amp;state, InputTs &amp;&amp;...ins) -&gt; reductor_fn&lt; estd::decay_t&lt; ReducingFnT &gt;,                                                               estd::decay_t&lt; InitialStateT &gt;,                                                               estd::decay_t&lt; InputTs &gt;... &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>empty_reductor</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a4c47717f6c502f590dc15f173f264eae</anchor>
      <arglist>(ReducingFnT &amp;&amp;step, InitialStateT &amp;&amp;state) -&gt; empty_reductor_fn&lt; estd::decay_t&lt; ReducingFnT &gt;,                                                                                       estd::decay_t&lt; InitialStateT &gt;,                                                                                       estd::decay_t&lt; InputTs &gt;... &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>run.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>run_8hpp</filename>
    <includes id="transduce_8hpp" name="transduce.hpp" local="no" imported="no">atria/xform/transduce.hpp</includes>
    <includes id="first__rf_8hpp" name="first_rf.hpp" local="no" imported="no">atria/xform/reducing/first_rf.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>void</type>
      <name>run</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a556bdf7d92cfc3f9678e478b2e0a7ac9</anchor>
      <arglist>(XformT &amp;&amp;xform, InputRangeTs &amp;&amp;...ranges)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>sequence.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>sequence_8hpp</filename>
    <includes id="reductor_8hpp" name="reductor.hpp" local="no" imported="no">atria/xform/reductor.hpp</includes>
    <includes id="meta_8hpp" name="meta.hpp" local="no" imported="no">atria/xform/meta.hpp</includes>
    <includes id="tuple__utils_8hpp" name="tuple_utils.hpp" local="no" imported="no">atria/xform/detail/tuple_utils.hpp</includes>
    <includes id="value__type_8hpp" name="value_type.hpp" local="no" imported="no">atria/meta/value_type.hpp</includes>
    <class kind="struct">atria::xform::sequence_range</class>
    <class kind="struct">atria::xform::sequence_range::iterator</class>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>sequence</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>acaa64702270f0f9f1ebf7c1d4d9cf2eb</anchor>
      <arglist>(XformT &amp;&amp;xform, const RangeTs &amp;...ranges) -&gt; sequence_range&lt;              typename boost::mpl::eval_if&lt;                              std::is_same&lt; ValueT, detail::deduce_value_type &gt;,                           result_of&lt; XformT, meta::value_t&lt; RangeTs &gt;... &gt;,                           meta::identity&lt; ValueT &gt; &gt;::type,           estd::decay_t&lt; XformT &gt;,           estd::decay_t&lt; RangeTs &gt;... &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>skip.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>skip_8hpp</filename>
    <includes id="state__traits_8hpp" name="state_traits.hpp" local="no" imported="no">atria/xform/state_traits.hpp</includes>
    <includes id="match__eggs_8hpp" name="match_eggs.hpp" local="no" imported="no">atria/variant/match_eggs.hpp</includes>
    <includes id="common__type_8hpp" name="common_type.hpp" local="no" imported="no">atria/meta/common_type.hpp</includes>
    <includes id="utility_8hpp" name="utility.hpp" local="no" imported="no">atria/estd/utility.hpp</includes>
    <class kind="struct">atria::xform::skip_state</class>
    <class kind="struct">atria::xform::is_skip_state</class>
    <class kind="struct">atria::xform::is_skip_state&lt; skip_state&lt; SkippedT, CalledT &gt; &gt;</class>
    <class kind="struct">atria::xform::state_traits&lt; skip_state&lt; SkippedT, CalledT &gt; &gt;</class>
    <class kind="struct">atria::xform::state_traits&lt; skip_state&lt; SkippedT, CalledT &gt; &gt;::can_not_do_that</class>
    <class kind="struct">atria::xform::skip_result</class>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>skip</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a7b5d683f19ef370bc5e121c89f861c89</anchor>
      <arglist>(ReducingFnT &amp;&amp;, StateT &amp;&amp;state, InputTs &amp;&amp;...) -&gt; skip_result_t&lt; ReducingFnT, StateT, InputTs... &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>call</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a52fea8a48eaf32278634f831a495d251</anchor>
      <arglist>(ReducingFnT &amp;&amp;step, StateT &amp;&amp;state, InputTs &amp;&amp;...ins) -&gt; estd::enable_if_t&lt;              is_skip_state&lt; estd::decay_t&lt; StateT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>state_traits.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>state__traits_8hpp</filename>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <includes id="utility_8hpp" name="utility.hpp" local="no" imported="no">atria/estd/utility.hpp</includes>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <class kind="struct">atria::xform::state_traits</class>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>state_complete</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a742ad6e9cabc139c89bf66d8dc78c9ca</anchor>
      <arglist>(T &amp;&amp;s) -&gt; decltype(state_traits_t&lt; T &gt;::complete(std::forward&lt; T &gt;(s)))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_is_reduced</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>aa3bd5ac59b27e0db927043add4734650</anchor>
      <arglist>(T &amp;&amp;s) -&gt; bool</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_data</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a39ee97ff60db7e300fcdea53ae64b08d</anchor>
      <arglist>(T &amp;&amp;s, D &amp;&amp;d) -&gt; decltype(state_traits_t&lt; T &gt;::data(std::forward&lt; T &gt;(s),                                                                                                           std::forward&lt; D &gt;(d)))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_unwrap</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a8f3d5f97c45a219e65ba34cd3838e7ed</anchor>
      <arglist>(T &amp;&amp;s) -&gt; decltype(state_traits_t&lt; T &gt;::unwrap(std::forward&lt; T &gt;(s)))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_unwrap_all</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a4b8a06f0fe7f2e877ce00ebb20feac76</anchor>
      <arglist>(T &amp;&amp;s) -&gt; decltype(state_traits_t&lt; T &gt;::unwrap_all(std::forward&lt; T &gt;(s)))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_rewrap</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a6a2fb9067174fbd25ff78adaeb41650f</anchor>
      <arglist>(T &amp;&amp;s, U &amp;&amp;x) -&gt; decltype(state_traits_t&lt; T &gt;::rewrap(std::forward&lt; T &gt;(s), std::forward&lt; U &gt;(x)))</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>state_wrapper.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>state__wrapper_8hpp</filename>
    <includes id="state__traits_8hpp" name="state_traits.hpp" local="no" imported="no">atria/xform/state_traits.hpp</includes>
    <class kind="struct">atria::xform::no_tag</class>
    <class kind="struct">atria::xform::state_wrapper</class>
    <class kind="struct">atria::xform::is_state_wrapper</class>
    <class kind="struct">atria::xform::is_state_wrapper&lt; _, state_wrapper&lt; T, S, D &gt; &gt;</class>
    <class kind="struct">atria::xform::state_traits&lt; state_wrapper&lt; TagT, StateT, DataT &gt; &gt;</class>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>wrap_state</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ad7b8b53c8727219bc6bbad59d8b58c1f</anchor>
      <arglist>(StateT &amp;&amp;next, DataT &amp;&amp;data=DataT{}) -&gt; state_wrapper&lt; TagT,                                                                       estd::decay_t&lt; StateT &gt;,                                                                       estd::decay_t&lt; DataT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_wrapper_complete</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a0e2b263b3e03295e68676c7df069f328</anchor>
      <arglist>(TagT, T &amp;&amp;s) -&gt; decltype(state_complete(state_unwrap(std::forward&lt; T &gt;(s))))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_wrapper_unwrap</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a0a1356003e10762cec1b6e68b4676ee8</anchor>
      <arglist>(TagT, T &amp;&amp;s) -&gt; decltype(std::get&lt; 0 &gt;(std::forward&lt; T &gt;(s)))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_wrapper_unwrap_all</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ab9b5e75829c1fdfe3f57451bc70790b0</anchor>
      <arglist>(TagT, T &amp;&amp;s) -&gt; decltype(state_unwrap_all(state_unwrap(std::forward&lt; T &gt;(s))))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_wrapper_rewrap</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a9d6df5b2f73d5e586e2dbce9a44fe747</anchor>
      <arglist>(TagT, T &amp;&amp;s, U &amp;&amp;x) -&gt; decltype(wrap_state&lt; TagT &gt;(                   state_rewrap(state_unwrap(std::forward&lt; T &gt;(s)), x),                   state_wrapper_data(std::forward&lt; T &gt;(s))))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_wrapper_data</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a8100207fd3c7ddf71e629248b76a184b</anchor>
      <arglist>(TagT tag, T &amp;&amp;s, D &amp;&amp;) -&gt; decltype(state_wrapper_data(tag, std::forward&lt; T &gt;(s)))</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>state_wrapper_data_is_reduced</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>af74cc4a347fd2ad83c01a0c7c35292de</anchor>
      <arglist>(TagT, DataT &amp;&amp;)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>state_wrapper_is_reduced</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>aab2250f9477d337be124b73f3ad9d2c8</anchor>
      <arglist>(TagT tag, T &amp;&amp;s)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>cat.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>cat_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="reduce__nested_8hpp" name="reduce_nested.hpp" local="no" imported="no">atria/xform/reduce_nested.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cat</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a7b3db0b1325b015399b0d50f75e33220</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>chain.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>chain_8hpp</filename>
    <includes id="empty__transducer__error_8hpp" name="empty_transducer_error.hpp" local="no" imported="no">atria/xform/detail/empty_transducer_error.hpp</includes>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="with__state_8hpp" name="with_state.hpp" local="no" imported="no">atria/xform/with_state.hpp</includes>
    <includes id="reduce__nested_8hpp" name="reduce_nested.hpp" local="no" imported="no">atria/xform/reduce_nested.hpp</includes>
    <includes id="comp_8hpp" name="comp.hpp" local="no" imported="no">atria/prelude/comp.hpp</includes>
    <includes id="identity_8hpp" name="identity.hpp" local="no" imported="no">atria/prelude/identity.hpp</includes>
    <includes id="copy__traits_8hpp" name="copy_traits.hpp" local="no" imported="no">atria/meta/copy_traits.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>constexpr auto</type>
      <name>chainr</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ad18c36bdd6e85b3a7f6584603386ec61</anchor>
      <arglist>(InputRangeT &amp;&amp;r) -&gt; chainr_t&lt; estd::decay_t&lt; InputRangeT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>chain</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ac2b85e8714c0aa88ddb6dcc59c3501e6</anchor>
      <arglist>(InputRangeTs &amp;&amp;...rs) -&gt; decltype(chainr(std::forward&lt; InputRangeTs &gt;(rs)...))</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>chainl</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a70d85a17047adedbda1892ac046e092d</anchor>
      <arglist>(InputRangeT &amp;&amp;r) -&gt; chainl_t&lt; estd::decay_t&lt; InputRangeT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>count.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>count_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="constantly_8hpp" name="constantly.hpp" local="no" imported="no">atria/prelude/constantly.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>constexpr auto</type>
      <name>count</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a355c4a75a7b2d4a537ef915446b4e307</anchor>
      <arglist>(InitT init=InitT{0}, StepT step=StepT{1}) -&gt; count_t&lt; InitT, StepT &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>cycle.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>cycle_8hpp</filename>
    <includes id="empty__transducer__error_8hpp" name="empty_transducer_error.hpp" local="no" imported="no">atria/xform/detail/empty_transducer_error.hpp</includes>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="comp_8hpp" name="comp.hpp" local="no" imported="no">atria/prelude/comp.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>constexpr auto</type>
      <name>cycle</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a6ca64e4188beed34b52a9ddc7e692bd5</anchor>
      <arglist>(InputRangeT &amp;&amp;r) -&gt; cycle_t&lt; estd::decay_t&lt; InputRangeT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>dedupe.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>dedupe_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="with__state_8hpp" name="with_state.hpp" local="no" imported="no">atria/xform/with_state.hpp</includes>
    <includes id="skip_8hpp" name="skip.hpp" local="no" imported="no">atria/xform/skip.hpp</includes>
    <includes id="tuplify_8hpp" name="tuplify.hpp" local="no" imported="no">atria/prelude/tuplify.hpp</includes>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="variable">
      <type>constexpr dedupe_t</type>
      <name>dedupe</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a4c6daf171c364c439a2595957a5d6b2d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>distinct.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>distinct_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="with__state_8hpp" name="with_state.hpp" local="no" imported="no">atria/xform/with_state.hpp</includes>
    <includes id="tuple__hash_8hpp" name="tuple_hash.hpp" local="no" imported="no">atria/estd/tuple_hash.hpp</includes>
    <includes id="tuplify_8hpp" name="tuplify.hpp" local="no" imported="no">atria/prelude/tuplify.hpp</includes>
    <includes id="functional_8hpp" name="functional.hpp" local="no" imported="no">atria/estd/functional.hpp</includes>
    <includes id="copy__traits_8hpp" name="copy_traits.hpp" local="no" imported="no">atria/meta/copy_traits.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="variable">
      <type>constexpr distinct_t</type>
      <name>distinct</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a71ceccfe79ea71598ee8534b2c7bade7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>drop.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>drop_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="skip_8hpp" name="skip.hpp" local="no" imported="no">atria/xform/skip.hpp</includes>
    <includes id="constantly_8hpp" name="constantly.hpp" local="no" imported="no">atria/prelude/constantly.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>drop</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a01f108701be19ec8d379b9f6b0515e53</anchor>
      <arglist>(IntegralT &amp;&amp;n) -&gt; drop_t&lt; estd::decay_t&lt; IntegralT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>drop_while.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>drop__while_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="skip_8hpp" name="skip.hpp" local="no" imported="no">atria/xform/skip.hpp</includes>
    <includes id="constantly_8hpp" name="constantly.hpp" local="no" imported="no">atria/prelude/constantly.hpp</includes>
    <includes id="functional_8hpp" name="functional.hpp" local="no" imported="no">atria/estd/functional.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>drop_while</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a38696dd462d8382acbb53035db399d75</anchor>
      <arglist>(PredicateT &amp;&amp;n) -&gt; drop_while_t&lt; estd::decay_t&lt; PredicateT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>each.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>each_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="functional_8hpp" name="functional.hpp" local="no" imported="no">atria/estd/functional.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>each</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ae2bc188bb24ad7c3799ad8198cbeb3c9</anchor>
      <arglist>(ActionT &amp;&amp;action) -&gt; each_t&lt; estd::decay_t&lt; ActionT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>eager.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>eager_8hpp</filename>
    <includes id="reduce__nested_8hpp" name="reduce_nested.hpp" local="no" imported="no">atria/xform/reduce_nested.hpp</includes>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="tuplify_8hpp" name="tuplify.hpp" local="no" imported="no">atria/prelude/tuplify.hpp</includes>
    <includes id="identity_8hpp" name="identity.hpp" local="no" imported="no">atria/prelude/identity.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>eager</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a2f58051c6b87fb2548954b6f9d744126</anchor>
      <arglist>(MappingT &amp;&amp;mapping) -&gt; eager_t&lt; estd::decay_t&lt; MappingT &gt; &gt;</arglist>
    </member>
    <member kind="variable">
      <type>constexpr sorted_t</type>
      <name>sorted</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a642cff3421f4c943d8f5039baa6feef9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr reversed_t</type>
      <name>reversed</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a9fc45ce6e33283e92568eee03414b0e1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>filter.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>filter_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="skip_8hpp" name="skip.hpp" local="no" imported="no">atria/xform/skip.hpp</includes>
    <includes id="functional_8hpp" name="functional.hpp" local="no" imported="no">atria/estd/functional.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>filter</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a80ba27e99da8878464eb743b464c368e</anchor>
      <arglist>(PredicateT &amp;&amp;predicate) -&gt; filter_t&lt; estd::decay_t&lt; PredicateT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>interleave.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>interleave_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="state__traits_8hpp" name="state_traits.hpp" local="no" imported="no">atria/xform/state_traits.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>interleave</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a862d2b68690c1c4f277f48d9b677d5de</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>interpose.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>interpose_8hpp</filename>
    <includes id="empty__transducer__error_8hpp" name="empty_transducer_error.hpp" local="no" imported="no">atria/xform/detail/empty_transducer_error.hpp</includes>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="with__state_8hpp" name="with_state.hpp" local="no" imported="no">atria/xform/with_state.hpp</includes>
    <includes id="copy__traits_8hpp" name="copy_traits.hpp" local="no" imported="no">atria/meta/copy_traits.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>constexpr auto</type>
      <name>interpose</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>aeaf09b40e364f41e2e0018926f5bf5ee</anchor>
      <arglist>(ValueTs &amp;&amp;...xs) -&gt; interpose_t&lt; estd::make_index_sequence&lt; sizeof...(ValueTs)&gt;,                                                               std::tuple&lt; estd::decay_t&lt; ValueTs &gt;... &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iter.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>iter_8hpp</filename>
    <includes id="empty__transducer__error_8hpp" name="empty_transducer_error.hpp" local="no" imported="no">atria/xform/detail/empty_transducer_error.hpp</includes>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="comp_8hpp" name="comp.hpp" local="no" imported="no">atria/prelude/comp.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>constexpr auto</type>
      <name>iter</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>acfab0c45a5f548e9a839f2060a45da77</anchor>
      <arglist>(InputRangeT &amp;&amp;r) -&gt; iter_t&lt; estd::decay_t&lt; InputRangeT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>map.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>map_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <includes id="functional_8hpp" name="functional.hpp" local="no" imported="no">atria/estd/functional.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>map</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a9f5d15acc0898885bc4386a7c9b41005</anchor>
      <arglist>(MappingT &amp;&amp;mapping) -&gt; map_t&lt; estd::decay_t&lt; MappingT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>map_indexed.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>map__indexed_8hpp</filename>
    <includes id="map_8hpp" name="map.hpp" local="no" imported="no">atria/xform/transducer/map.hpp</includes>
    <includes id="count_8hpp" name="count.hpp" local="no" imported="no">atria/xform/transducer/count.hpp</includes>
    <includes id="comp_8hpp" name="comp.hpp" local="no" imported="no">atria/prelude/comp.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>constexpr auto</type>
      <name>map_indexed</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a9f02ae83038b034fafb27e2f284499f1</anchor>
      <arglist>(MappingT &amp;&amp;mapping) -&gt; decltype(comp(                   count(),                   map(std::forward&lt; MappingT &gt;(mapping))))</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>mapcat.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>mapcat_8hpp</filename>
    <includes id="cat_8hpp" name="cat.hpp" local="no" imported="no">atria/xform/transducer/cat.hpp</includes>
    <includes id="map_8hpp" name="map.hpp" local="no" imported="no">atria/xform/transducer/map.hpp</includes>
    <includes id="comp_8hpp" name="comp.hpp" local="no" imported="no">atria/prelude/comp.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>mapcat</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a980d70b208be73e99b32bc073ec92412</anchor>
      <arglist>(MappingT &amp;&amp;mapping) -&gt; decltype(comp(                   cat,                   map(std::forward&lt; MappingT &gt;(mapping))))</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>partition.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>partition_8hpp</filename>
    <includes id="reduce_8hpp" name="reduce.hpp" local="no" imported="no">atria/xform/reduce.hpp</includes>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="skip_8hpp" name="skip.hpp" local="no" imported="no">atria/xform/skip.hpp</includes>
    <includes id="tuplify_8hpp" name="tuplify.hpp" local="no" imported="no">atria/prelude/tuplify.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>partition</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a83103216261e92d2147ce41252272f76</anchor>
      <arglist>(IntegralT &amp;&amp;n) -&gt; partition_t&lt; estd::decay_t&lt; IntegralT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>partition_by.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>partition__by_8hpp</filename>
    <includes id="reduce_8hpp" name="reduce.hpp" local="no" imported="no">atria/xform/reduce.hpp</includes>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="skip_8hpp" name="skip.hpp" local="no" imported="no">atria/xform/skip.hpp</includes>
    <includes id="functional_8hpp" name="functional.hpp" local="no" imported="no">atria/estd/functional.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>partition_by</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a89e3ff42b7cdfce00041ef5be8c89efc</anchor>
      <arglist>(MappingT &amp;&amp;mapping) -&gt; partition_by_t&lt; estd::decay_t&lt; MappingT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>product.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>product_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="empty__transducer__error_8hpp" name="empty_transducer_error.hpp" local="no" imported="no">atria/xform/detail/empty_transducer_error.hpp</includes>
    <includes id="reduce__nested_8hpp" name="reduce_nested.hpp" local="no" imported="no">atria/xform/reduce_nested.hpp</includes>
    <includes id="comp_8hpp" name="comp.hpp" local="no" imported="no">atria/prelude/comp.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>constexpr auto</type>
      <name>product</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a4fa098e18370e4117e3ae707e280d2bb</anchor>
      <arglist>(InputRangeT &amp;&amp;r) -&gt; product_t&lt; estd::decay_t&lt; InputRangeT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>random_sample.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>random__sample_8hpp</filename>
    <includes id="filter_8hpp" name="filter.hpp" local="no" imported="no">atria/xform/transducer/filter.hpp</includes>
    <includes id="map_8hpp" name="map.hpp" local="no" imported="no">atria/xform/transducer/map.hpp</includes>
    <includes id="complement_8hpp" name="complement.hpp" local="no" imported="no">atria/prelude/complement.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>random_sample</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>abb6065c740d69641dc343d90814152b0</anchor>
      <arglist>(ProbabilityT prob, GeneratorT generator=GeneratorT{}) -&gt; decltype(filter(detail::random_sampler&lt; ProbabilityT, GeneratorT &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>range.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>range_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="transducer_2take_8hpp" name="take.hpp" local="no" imported="no">atria/xform/transducer/take.hpp</includes>
    <includes id="count_8hpp" name="count.hpp" local="no" imported="no">atria/xform/transducer/count.hpp</includes>
    <includes id="comp_8hpp" name="comp.hpp" local="no" imported="no">atria/prelude/comp.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>constexpr auto</type>
      <name>range</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a416bf0ab5631d3cb304f6fdd3db0789a</anchor>
      <arglist>(StopT &amp;&amp;stop) -&gt; decltype(comp(                   count(),                   take(std::forward&lt; StopT &gt;(stop))))</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>read.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>read_8hpp</filename>
    <includes id="maybe__reduced_8hpp" name="maybe_reduced.hpp" local="no" imported="no">atria/xform/maybe_reduced.hpp</includes>
    <includes id="skip_8hpp" name="skip.hpp" local="no" imported="no">atria/xform/skip.hpp</includes>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="comp_8hpp" name="comp.hpp" local="no" imported="no">atria/prelude/comp.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>read</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a433828f060fdc4d07dcd50c9486833af</anchor>
      <arglist>(InputStreamT &amp;stream) -&gt; read_t&lt; T, std::reference_wrapper&lt; InputStreamT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>readbuf.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>readbuf_8hpp</filename>
    <includes id="maybe__reduced_8hpp" name="maybe_reduced.hpp" local="no" imported="no">atria/xform/maybe_reduced.hpp</includes>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="comp_8hpp" name="comp.hpp" local="no" imported="no">atria/prelude/comp.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>readbuf</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a6dac4023e221361610f4f65fee508057</anchor>
      <arglist>(InputStreamT &amp;stream) -&gt; readbuf_t&lt; std::reference_wrapper&lt; InputStreamT &gt;, std::array&lt; char, N &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>readbuf</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a9a8a0ac5d4f0bc817d5f1b4e11b11b30</anchor>
      <arglist>(InputStreamT &amp;stream, std::size_t n) -&gt; readbuf_t&lt; std::reference_wrapper&lt; InputStreamT &gt;, std::vector&lt; char &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>remove.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>remove_8hpp</filename>
    <includes id="filter_8hpp" name="filter.hpp" local="no" imported="no">atria/xform/transducer/filter.hpp</includes>
    <includes id="map_8hpp" name="map.hpp" local="no" imported="no">atria/xform/transducer/map.hpp</includes>
    <includes id="complement_8hpp" name="complement.hpp" local="no" imported="no">atria/prelude/complement.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>remove</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ad6801522a4749259f1da08257065abc3</anchor>
      <arglist>(PredicateT &amp;&amp;pred) -&gt; decltype(filter(complement(std::forward&lt; PredicateT &gt;(pred))))</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>repeat.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>repeat_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="transducer_2take_8hpp" name="take.hpp" local="no" imported="no">atria/xform/transducer/take.hpp</includes>
    <includes id="comp_8hpp" name="comp.hpp" local="no" imported="no">atria/prelude/comp.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>constexpr auto</type>
      <name>repeat</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a93215c74409bd3b594605eaa624d4d18</anchor>
      <arglist>(ValueT &amp;&amp;r) -&gt; repeat_t&lt; estd::decay_t&lt; ValueT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>repeatn</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>abc8200b8f34aaaf847917234ce315d82</anchor>
      <arglist>(IntegralT &amp;&amp;n, ValueTs &amp;&amp;...rs) -&gt; decltype(comp(repeat(std::forward&lt; ValueTs &gt;(rs)...),                               take(std::forward&lt; IntegralT &gt;(n))))</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>replace.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>replace_8hpp</filename>
    <includes id="map_8hpp" name="map.hpp" local="no" imported="no">atria/xform/transducer/map.hpp</includes>
    <includes id="tuplify_8hpp" name="tuplify.hpp" local="no" imported="no">atria/prelude/tuplify.hpp</includes>
    <includes id="utils_8hpp" name="utils.hpp" local="no" imported="no">atria/meta/utils.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>replace</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>aa04b4d4796efe53d507356cb40d10ea0</anchor>
      <arglist>(TableT &amp;&amp;table) -&gt; decltype(map(detail::lookup_or_key&lt; estd::decay_t&lt; TableT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>replace_all</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>af34877a89c42bfdf11a53c7218f71302</anchor>
      <arglist>(TableT &amp;&amp;table) -&gt; decltype(map(detail::lookup_default&lt; estd::decay_t&lt; TableT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>replace_all_safe</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>aaad19ba27a1533eb710ce84f9c300915</anchor>
      <arglist>(TableT &amp;&amp;table) -&gt; decltype(map(detail::lookup_safe&lt; estd::decay_t&lt; TableT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>sink.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>sink_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="functional_8hpp" name="functional.hpp" local="no" imported="no">atria/estd/functional.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>sink</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>af614a13bb66957508876cefc21cb4902</anchor>
      <arglist>(ActionT &amp;&amp;action) -&gt; sink_t&lt; estd::decay_t&lt; ActionT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>take_nth.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>take__nth_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="with__state_8hpp" name="with_state.hpp" local="no" imported="no">atria/xform/with_state.hpp</includes>
    <includes id="copy__traits_8hpp" name="copy_traits.hpp" local="no" imported="no">atria/meta/copy_traits.hpp</includes>
    <includes id="constantly_8hpp" name="constantly.hpp" local="no" imported="no">atria/prelude/constantly.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>take_nth</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a17787884a59f85db0f31190809a9de80</anchor>
      <arglist>(IntegralT &amp;&amp;n) -&gt; take_nth_t&lt; estd::decay_t&lt; IntegralT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>take_while.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>take__while_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="maybe__reduced_8hpp" name="maybe_reduced.hpp" local="no" imported="no">atria/xform/maybe_reduced.hpp</includes>
    <includes id="skip_8hpp" name="skip.hpp" local="no" imported="no">atria/xform/skip.hpp</includes>
    <includes id="functional_8hpp" name="functional.hpp" local="no" imported="no">atria/estd/functional.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>take_while</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a68949f8b8b3369cd89c0f5e522b762c2</anchor>
      <arglist>(PredicateT &amp;&amp;p) -&gt; take_while_t&lt; estd::decay_t&lt; PredicateT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>traced.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>traced_8hpp</filename>
    <includes id="trace_8hpp" name="trace.hpp" local="no" imported="no">atria/prelude/trace.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>traced</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a1c5626f067144894d8ba89075c02120a</anchor>
      <arglist>(std::string message) -&gt; decltype(map(tracer</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>unzip.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>unzip_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="get__index__sequence_8hpp" name="get_index_sequence.hpp" local="no" imported="no">atria/meta/get_index_sequence.hpp</includes>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>unzip</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>abe5308d966fbf95d317511a706d6d20a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>write.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>write_8hpp</filename>
    <includes id="state__wrapper_8hpp" name="state_wrapper.hpp" local="no" imported="no">atria/xform/state_wrapper.hpp</includes>
    <includes id="with__state_8hpp" name="with_state.hpp" local="no" imported="no">atria/xform/with_state.hpp</includes>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <includes id="comp_8hpp" name="comp.hpp" local="no" imported="no">atria/prelude/comp.hpp</includes>
    <includes id="copy__traits_8hpp" name="copy_traits.hpp" local="no" imported="no">atria/meta/copy_traits.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>write</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a59baa0dcd3ba01cca2f1eea15d284c8e</anchor>
      <arglist>(OutputStreamT &amp;stream, InSeparatorT in_sep=InSeparatorT{}) -&gt; write_t&lt; std::reference_wrapper&lt; OutputStreamT &gt;,                                               InSeparatorT,                                               InSeparatorT &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>writebuf.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>writebuf_8hpp</filename>
    <includes id="transducer__impl_8hpp" name="transducer_impl.hpp" local="no" imported="no">atria/xform/transducer_impl.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>writebuf</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a17cf9b4f857005aa681a5f59b78b9d11</anchor>
      <arglist>(OutputStreamT &amp;stream) -&gt; writebuf_t&lt; std::reference_wrapper&lt; OutputStreamT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>zip.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/transducer/</path>
    <filename>zip_8hpp</filename>
    <includes id="tuplify_8hpp" name="tuplify.hpp" local="no" imported="no">atria/prelude/tuplify.hpp</includes>
    <includes id="map_8hpp" name="map.hpp" local="no" imported="no">atria/xform/transducer/map.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="variable">
      <type>const map_t&lt; tuplify_t &gt;</type>
      <name>zip</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a3002569b1ecc9b8b0e17d0de591c2915</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>transducer_impl.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>transducer__impl_8hpp</filename>
    <includes id="type__traits_8hpp" name="type_traits.hpp" local="no" imported="no">atria/estd/type_traits.hpp</includes>
    <includes id="utility_8hpp" name="utility.hpp" local="no" imported="no">atria/estd/utility.hpp</includes>
    <class kind="struct">atria::xform::transducer_impl</class>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="file">
    <name>with_state.hpp</name>
    <path>/home/travis/build/Ableton/atria/src/atria/xform/</path>
    <filename>with__state_8hpp</filename>
    <includes id="any__state_8hpp" name="any_state.hpp" local="no" imported="no">atria/xform/any_state.hpp</includes>
    <includes id="lazy__enable__if_8hpp" name="lazy_enable_if.hpp" local="no" imported="no">atria/meta/lazy_enable_if.hpp</includes>
    <namespace>atria</namespace>
    <namespace>atria::xform</namespace>
    <member kind="function">
      <type>auto</type>
      <name>with_state</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a688e55a0bcb50339f31752d3d49ba7d9</anchor>
      <arglist>(StateT &amp;&amp;st, UnwrappedFn &amp;&amp;, WrappedFn &amp;&amp;fn) -&gt; meta::lazy_enable_if_t&lt;              !std::is_same&lt;                      estd::decay_t&lt; StateT &gt;,                   estd::decay_t&lt; decltype(state_complete(st))&gt;           &gt;::value,           std::result_of&lt; WrappedFn(StateT)&gt;   &gt;</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>atria::testing::variant_spy::all_variants</name>
    <filename>structatria_1_1testing_1_1variant__spy_1_1all__variants.html</filename>
  </compound>
  <compound kind="class">
    <name>atria::xform::any_state</name>
    <filename>classatria_1_1xform_1_1any__state.html</filename>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::front_impl&lt; atria::meta::std_tuple_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1front__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::pop_front_impl&lt; atria::meta::std_tuple_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1pop__front__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::empty_impl&lt; atria::meta::std_tuple_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1empty__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::push_back_impl&lt; atria::meta::std_tuple_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1push__back__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::push_front_impl&lt; atria::meta::std_tuple_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1push__front__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::size_impl&lt; atria::meta::std_tuple_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1size__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::at_impl&lt; atria::meta::std_tuple_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1at__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::back_impl&lt; atria::meta::std_tuple_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1back__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::clear_impl&lt; atria::meta::std_tuple_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1clear__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1pop__back__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::begin_impl&lt; atria::meta::std_tuple_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1begin__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::end_impl&lt; atria::meta::std_tuple_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1end__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::front_impl&lt; atria::meta::pack_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1front__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::empty_impl&lt; atria::meta::pack_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1empty__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::pop_front_impl&lt; atria::meta::pack_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1pop__front__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::push_front_impl&lt; atria::meta::pack_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1push__front__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::push_back_impl&lt; atria::meta::pack_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1push__back__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::size_impl&lt; atria::meta::pack_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1size__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::at_impl&lt; atria::meta::pack_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1at__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::back_impl&lt; atria::meta::pack_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1back__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::clear_impl&lt; atria::meta::pack_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1clear__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::pop_back_impl&lt; atria::meta::pack_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1pop__back__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::begin_impl&lt; atria::meta::pack_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1begin__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::end_impl&lt; atria::meta::pack_tag &gt;::apply</name>
    <filename>structboost_1_1mpl_1_1end__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::push_front_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; Args... &gt;, T &gt;</name>
    <filename>structboost_1_1mpl_1_1push__front__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply_3_01atria_168ec05978b41f4c505ab63e52ddad1e4.html</filename>
    <templarg></templarg>
    <templarg>Args</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::push_back_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; Args... &gt;, T &gt;</name>
    <filename>structboost_1_1mpl_1_1push__back__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply_3_01atria_1_f49ef35a24259998c151abb70357a262.html</filename>
    <templarg></templarg>
    <templarg>Args</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::pop_front_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; First, Types... &gt; &gt;</name>
    <filename>structboost_1_1mpl_1_1pop__front__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply_3_01atria_1_209c11484cc18a6080b8124e0bb5a9e3.html</filename>
    <templarg></templarg>
    <templarg>Types</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::front_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; T, Ts... &gt; &gt;</name>
    <filename>structboost_1_1mpl_1_1front__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply_3_01atria_1_1metaafd3b017d3c85cac1b457e3d468ef178.html</filename>
    <templarg></templarg>
    <templarg>Ts</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::empty_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; Ts... &gt; &gt;</name>
    <filename>structboost_1_1mpl_1_1empty__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply_3_01atria_1_1meta8a11dfc374735b44eb57da8b0063204d.html</filename>
    <templarg>Ts</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::size_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; Ts... &gt; &gt;</name>
    <filename>structboost_1_1mpl_1_1size__impl_3_01atria_1_1meta_1_1pack__tag_01_4_1_1apply_3_01atria_1_1meta_1_1pack_3_01_ts_8_8_8_01_4_01_4.html</filename>
    <templarg>Ts</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::push_front_impl&lt; atria::meta::std_tuple_tag &gt;::apply&lt; std::tuple&lt; Args... &gt;, T &gt;</name>
    <filename>structboost_1_1mpl_1_1push__front__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1apply_3_01seb5514c636a19d143ea214deabf2c057.html</filename>
    <templarg></templarg>
    <templarg>Args</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::push_back_impl&lt; atria::meta::std_tuple_tag &gt;::apply&lt; std::tuple&lt; Args... &gt;, T &gt;</name>
    <filename>structboost_1_1mpl_1_1push__back__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1apply_3_01st212b018f89ff4b11e2b8cdb170213d3d.html</filename>
    <templarg></templarg>
    <templarg>Args</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::pop_front_impl&lt; atria::meta::std_tuple_tag &gt;::apply&lt; std::tuple&lt; First, Types... &gt; &gt;</name>
    <filename>structboost_1_1mpl_1_1pop__front__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1apply_3_01std91f25010509e075db465cb424972b71.html</filename>
    <templarg></templarg>
    <templarg>Types</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::apply_impl</name>
    <filename>structboost_1_1mpl_1_1pop__back__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1apply__impl.html</filename>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::apply_impl&lt; Tuple, tuple_seq&lt; S... &gt; &gt;</name>
    <filename>structboost_1_1mpl_1_1pop__back__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1apply__impl_3f7d1f5aecfbde9b8e3c8a13c4f06e41b.html</filename>
    <templarg></templarg>
    <templarg>S</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::at_impl&lt; atria::meta::pack_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1at__impl_3_01atria_1_1meta_1_1pack__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::at_impl&lt; atria::meta::pack_tag &gt;::apply</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::at_impl&lt; atria::meta::std_tuple_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1at__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::at_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::back_impl&lt; atria::meta::pack_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1back__impl_3_01atria_1_1meta_1_1pack__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::back_impl&lt; atria::meta::pack_tag &gt;::apply</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::back_impl&lt; atria::meta::std_tuple_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1back__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::back_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::begin_impl&lt; atria::meta::pack_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1begin__impl_3_01atria_1_1meta_1_1pack__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::begin_impl&lt; atria::meta::pack_tag &gt;::apply</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::begin_impl&lt; atria::meta::std_tuple_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1begin__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::begin_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
  </compound>
  <compound kind="class">
    <name>atria::testing::benchmark_runner</name>
    <filename>classatria_1_1testing_1_1benchmark__runner.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::testing::benchmark_runner_error</name>
    <filename>structatria_1_1testing_1_1benchmark__runner__error.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::testing::benchmark_settings</name>
    <filename>structatria_1_1testing_1_1benchmark__settings.html</filename>
    <member kind="variable">
      <type>unsigned</type>
      <name>iterations</name>
      <anchorfile>structatria_1_1testing_1_1benchmark__settings.html</anchorfile>
      <anchor>adc2f6fefd1cedc6f626ffc175328efaf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>measurements</name>
      <anchorfile>structatria_1_1testing_1_1benchmark__settings.html</anchorfile>
      <anchor>a8cdf642320744913078a12154b192af1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::size_t</type>
      <name>size</name>
      <anchorfile>structatria_1_1testing_1_1benchmark__settings.html</anchorfile>
      <anchor>a15be4f36d9c953254b9d6d64bbc8590e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>verbose</name>
      <anchorfile>structatria_1_1testing_1_1benchmark__settings.html</anchorfile>
      <anchor>ab3f078684998b83967d507d0f453f454</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>atria::testing::benchmark_suite</name>
    <filename>classatria_1_1testing_1_1benchmark__suite.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>atria::testing::benchmark_suite&lt; void &gt;</name>
    <filename>classatria_1_1testing_1_1benchmark__suite_3_01void_01_4.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::meta::bottom</name>
    <filename>structatria_1_1meta_1_1bottom.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::xform::state_traits&lt; skip_state&lt; SkippedT, CalledT &gt; &gt;::can_not_do_that</name>
    <filename>structatria_1_1xform_1_1state__traits_3_01skip__state_3_01_skipped_t_00_01_called_t_01_4_01_4_1_1can__not__do__that.html</filename>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::clear_impl&lt; atria::meta::pack_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1clear__impl_3_01atria_1_1meta_1_1pack__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::clear_impl&lt; atria::meta::pack_tag &gt;::apply</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::clear_impl&lt; atria::meta::std_tuple_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1clear__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::clear_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
  </compound>
  <compound kind="struct">
    <name>atria::meta::common_type</name>
    <filename>structatria_1_1meta_1_1common__type.html</filename>
    <templarg>Ts</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::common_type&lt; T, Ts... &gt;</name>
    <filename>structatria_1_1meta_1_1common__type_3_01_t_00_01_ts_8_8_8_01_4.html</filename>
    <templarg></templarg>
    <templarg>Ts</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::common_type&lt;&gt;</name>
    <filename>structatria_1_1meta_1_1common__type_3_4.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::prelude::complement_t</name>
    <filename>structatria_1_1prelude_1_1complement__t.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::prelude::constantly_t</name>
    <filename>structatria_1_1prelude_1_1constantly__t.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::copy_cv</name>
    <filename>structatria_1_1meta_1_1copy__cv.html</filename>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::copy_decay</name>
    <filename>structatria_1_1meta_1_1copy__decay.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base>copy_reference&lt; OrigT, copy_cv_t&lt; estd::remove_reference_t&lt; OrigT &gt;, DestT &gt; &gt;</base>
  </compound>
  <compound kind="struct">
    <name>atria::meta::copy_reference</name>
    <filename>structatria_1_1meta_1_1copy__reference.html</filename>
    <templarg>OrigT</templarg>
    <templarg>DestT</templarg>
  </compound>
  <compound kind="class">
    <name>copy_reference&lt; OrigT, copy_cv_t&lt; estd::remove_reference_t&lt; OrigT &gt;, DestT &gt; &gt;</name>
    <filename>structatria_1_1meta_1_1copy__reference.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::testing::copy_spy</name>
    <filename>structatria_1_1testing_1_1copy__spy.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::copy_trait</name>
    <filename>structatria_1_1meta_1_1copy__trait.html</filename>
    <templarg>TraitCheckMF</templarg>
    <templarg>TraitAddMf</templarg>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::could_not_find_common_type</name>
    <filename>structatria_1_1meta_1_1could__not__find__common__type.html</filename>
    <templarg>Ts</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::could_not_get_index_sequence</name>
    <filename>structatria_1_1meta_1_1could__not__get__index__sequence.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::testing::mocks::defaulting</name>
    <filename>structatria_1_1testing_1_1mocks_1_1defaulting.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::deref&lt; atria::meta::pack_iterator&lt;  atria::meta::pack&lt; First, Args... &gt; &gt; &gt;</name>
    <filename>structboost_1_1mpl_1_1deref_3_01atria_1_1meta_1_1pack__iterator_3_01_01atria_1_1meta_1_1pack_3_0ee2e90bf33f5737ede960e670ef4c13a.html</filename>
    <templarg></templarg>
    <templarg>Args</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::deref&lt; atria::meta::std_tuple_iterator&lt; std::tuple&lt; First, Args... &gt; &gt; &gt;</name>
    <filename>structboost_1_1mpl_1_1deref_3_01atria_1_1meta_1_1std__tuple__iterator_3_01std_1_1tuple_3_01_firsd03b90aace3c7c925a319c7aba0c004c.html</filename>
    <templarg></templarg>
    <templarg>Args</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::detected_any</name>
    <filename>structatria_1_1meta_1_1detected__any.html</filename>
    <templarg></templarg>
    <templarg>Ops</templarg>
  </compound>
  <compound kind="class">
    <name>detected_any&lt; T, detail::value_type_t, detail::iterator_value_t, detail::dereference_t, detail::getter_t &gt;</name>
    <filename>structatria_1_1meta_1_1detected__any.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::meta::detected_any&lt; T, Op &gt;</name>
    <filename>structatria_1_1meta_1_1detected__any_3_01_t_00_01_op_01_4.html</filename>
    <templarg></templarg>
    <templarg>Op</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::detected_any&lt; T, Op, Ops... &gt;</name>
    <filename>structatria_1_1meta_1_1detected__any_3_01_t_00_01_op_00_01_ops_8_8_8_01_4.html</filename>
    <templarg></templarg>
    <templarg>Op</templarg>
    <templarg>Ops</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::xform::emplace_back_rf_t</name>
    <filename>structatria_1_1xform_1_1emplace__back__rf__t.html</filename>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::empty_impl&lt; atria::meta::pack_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1empty__impl_3_01atria_1_1meta_1_1pack__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::empty_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::empty_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; Ts... &gt; &gt;</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::empty_impl&lt; atria::meta::std_tuple_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1empty__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::empty_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
  </compound>
  <compound kind="struct">
    <name>atria::xform::empty_reductor_fn</name>
    <filename>structatria_1_1xform_1_1empty__reductor__fn.html</filename>
    <templarg>ReducingFnT</templarg>
    <templarg>InitialStateT</templarg>
    <templarg>InputTs</templarg>
    <base>reductor_fn_base&lt; detail::caller&lt; estd::decay_t&lt; ReducingFnT &gt; &gt;, estd::decay_t&lt; skip_result_t&lt; ReducingFnT, InitialStateT, InputTs... &gt; &gt;, InputTs... &gt;</base>
  </compound>
  <compound kind="class">
    <name>empty_reductor_fn&lt; ReducingFnT, InitialStateT, InputTs... &gt;</name>
    <filename>structatria_1_1xform_1_1empty__reductor__fn.html</filename>
    <base>reductor_fn_base&lt; detail::caller&lt; estd::decay_t&lt; ReducingFnT &gt; &gt;, estd::decay_t&lt; skip_result_t&lt; ReducingFnT, InitialStateT, InputTs... &gt; &gt;, InputTs... &gt;</base>
  </compound>
  <compound kind="struct">
    <name>atria::xform::empty_reductor_fn&lt; ReducingFnT, InitialStateT, meta::pack&lt; InputTs... &gt; &gt;</name>
    <filename>structatria_1_1xform_1_1empty__reductor__fn_3_01_reducing_fn_t_00_01_initial_state_t_00_01meta_1c4281aba4e6bb984f4d262b3b6c3fb56.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg>InputTs</templarg>
    <base>empty_reductor_fn&lt; ReducingFnT, InitialStateT, InputTs... &gt;</base>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::end_impl&lt; atria::meta::pack_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1end__impl_3_01atria_1_1meta_1_1pack__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::end_impl&lt; atria::meta::pack_tag &gt;::apply</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::end_impl&lt; atria::meta::std_tuple_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1end__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::end_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
  </compound>
  <compound kind="struct">
    <name>atria::xform::first_rf_t</name>
    <filename>structatria_1_1xform_1_1first__rf__t.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::meta::from_void</name>
    <filename>structatria_1_1meta_1_1from__void.html</filename>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::front_impl&lt; atria::meta::pack_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1front__impl_3_01atria_1_1meta_1_1pack__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::front_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::front_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; T, Ts... &gt; &gt;</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::front_impl&lt; atria::meta::std_tuple_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1front__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::front_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
  </compound>
  <compound kind="struct">
    <name>atria::meta::get_value_type</name>
    <filename>structatria_1_1meta_1_1get__value__type.html</filename>
    <templarg></templarg>
    <base>detected_any&lt; T, detail::value_type_t, detail::iterator_value_t, detail::dereference_t, detail::getter_t &gt;</base>
  </compound>
  <compound kind="struct">
    <name>std::hash&lt; atria::funken::structure&lt; T &gt; &gt;</name>
    <filename>structstd_1_1hash_3_01atria_1_1funken_1_1structure_3_01_t_01_4_01_4.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>std::hash&lt; tuple&lt; Ts... &gt; &gt;</name>
    <filename>structstd_1_1hash_3_01tuple_3_01_ts_8_8_8_01_4_01_4.html</filename>
    <templarg>Ts</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::identity</name>
    <filename>structatria_1_1meta_1_1identity.html</filename>
    <templarg>T</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::prelude::identity_t</name>
    <filename>structatria_1_1prelude_1_1identity__t.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::prelude::identity_t_</name>
    <filename>structatria_1_1prelude_1_1identity__t__.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::meta::if_any</name>
    <filename>structatria_1_1meta_1_1if__any.html</filename>
    <templarg></templarg>
    <templarg>Mfs</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::if_any&lt; T, Mf &gt;</name>
    <filename>structatria_1_1meta_1_1if__any_3_01_t_00_01_mf_01_4.html</filename>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::if_any&lt; T, Mf, Mfs... &gt;</name>
    <filename>structatria_1_1meta_1_1if__any_3_01_t_00_01_mf_00_01_mfs_8_8_8_01_4.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg>Mfs</templarg>
  </compound>
  <compound kind="class">
    <name>atria::funken::inoutput</name>
    <filename>classatria_1_1funken_1_1inoutput.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>atria::funken::input</name>
    <filename>classatria_1_1funken_1_1input.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::estd::integer_sequence</name>
    <filename>structatria_1_1estd_1_1integer__sequence.html</filename>
    <templarg></templarg>
    <templarg>Ints</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::xform::is_skip_state</name>
    <filename>structatria_1_1xform_1_1is__skip__state.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::xform::is_skip_state&lt; skip_state&lt; SkippedT, CalledT &gt; &gt;</name>
    <filename>structatria_1_1xform_1_1is__skip__state_3_01skip__state_3_01_skipped_t_00_01_called_t_01_4_01_4.html</filename>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::xform::is_state_wrapper</name>
    <filename>structatria_1_1xform_1_1is__state__wrapper.html</filename>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::xform::is_state_wrapper&lt; _, state_wrapper&lt; T, S, D &gt; &gt;</name>
    <filename>structatria_1_1xform_1_1is__state__wrapper_3_01___00_01state__wrapper_3_01_t_00_01_s_00_01_d_01_4_01_4.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::xform::sequence_range::iterator</name>
    <filename>structatria_1_1xform_1_1sequence__range_1_1iterator.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::xform::last_rf_t</name>
    <filename>structatria_1_1xform_1_1last__rf__t.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::meta::lazy_detected_or</name>
    <filename>structatria_1_1meta_1_1lazy__detected__or.html</filename>
    <templarg></templarg>
    <templarg>Op</templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::lazy_enable_if</name>
    <filename>structatria_1_1meta_1_1lazy__enable__if.html</filename>
    <templarg>C</templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::xform::maybe_reduced_tag</name>
    <filename>structatria_1_1xform_1_1maybe__reduced__tag.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::meta::models</name>
    <filename>structatria_1_1meta_1_1models.html</filename>
    <templarg>ConceptSig</templarg>
    <templarg>Enable</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::models&lt;                  ConceptSpecT(Ts...),           estd::void_t&lt;                                                  decltype(std::declval&lt; ConceptSpecT &gt;().requires_(                                                                                                                                   std::declval&lt; Ts &gt;()...))                           &gt;           &gt;</name>
    <filename>structatria_1_1meta_1_1models_3_01_01_01_01_01_01_01_01_01_01_01_01_01_01_01_01_01_01_concept_sp7cf6b5847602bcb884f5151b85331b66.html</filename>
    <templarg></templarg>
    <templarg>Ts</templarg>
  </compound>
  <compound kind="class">
    <name>models&lt; ConceptSpecT(T)&gt;</name>
    <filename>structatria_1_1meta_1_1models.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::meta::models_</name>
    <filename>structatria_1_1meta_1_1models__.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base>models&lt; ConceptSpecT(T)&gt;</base>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::next&lt; atria::meta::pack_iterator&lt;  atria::meta::pack&lt; First, Args... &gt; &gt; &gt;</name>
    <filename>structboost_1_1mpl_1_1next_3_01atria_1_1meta_1_1pack__iterator_3_01_01atria_1_1meta_1_1pack_3_010bcef55fe488963c67e64528bc17a2d4.html</filename>
    <templarg></templarg>
    <templarg>Args</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::next&lt; atria::meta::std_tuple_iterator&lt; std::tuple&lt; First, Args... &gt; &gt; &gt;</name>
    <filename>structboost_1_1mpl_1_1next_3_01atria_1_1meta_1_1std__tuple__iterator_3_01std_1_1tuple_3_01_first709229a3738552992f955d44cb278216.html</filename>
    <templarg></templarg>
    <templarg>Args</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::xform::no_tag</name>
    <filename>structatria_1_1xform_1_1no__tag.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::funken::no_value_error</name>
    <filename>structatria_1_1funken_1_1no__value__error.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::estd::nonesuch</name>
    <filename>structatria_1_1estd_1_1nonesuch.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::meta::noop_t</name>
    <filename>structatria_1_1meta_1_1noop__t.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::variant::otherwise_t</name>
    <filename>structatria_1_1variant_1_1otherwise__t.html</filename>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>atria::funken::output</name>
    <filename>classatria_1_1funken_1_1output.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::xform::output_of</name>
    <filename>structatria_1_1xform_1_1output__of.html</filename>
    <templarg></templarg>
    <templarg>InputTs</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::xform::output_of&lt; XformT, meta::pack&lt; InputTs... &gt; &gt;</name>
    <filename>structatria_1_1xform_1_1output__of_3_01_xform_t_00_01meta_1_1pack_3_01_input_ts_8_8_8_01_4_01_4.html</filename>
    <templarg></templarg>
    <templarg>InputTs</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::xform::output_rf_t</name>
    <filename>structatria_1_1xform_1_1output__rf__t.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::meta::pack</name>
    <filename>structatria_1_1meta_1_1pack.html</filename>
    <templarg>Ts</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::pack_iterator</name>
    <filename>structatria_1_1meta_1_1pack__iterator.html</filename>
    <templarg>Args</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::pack_iterator&lt; atria::meta::pack&lt; Args... &gt; &gt;</name>
    <filename>structatria_1_1meta_1_1pack__iterator_3_01atria_1_1meta_1_1pack_3_01_args_8_8_8_01_4_01_4.html</filename>
    <templarg>Args</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::pop_back_impl&lt; atria::meta::pack_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1pop__back__impl_3_01atria_1_1meta_1_1pack__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::pop_back_impl&lt; atria::meta::pack_tag &gt;::apply</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1pop__back__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::apply_impl</class>
    <class kind="struct">boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::apply_impl&lt; Tuple, tuple_seq&lt; S... &gt; &gt;</class>
    <class kind="struct">boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::tuple_gens</class>
    <class kind="struct">boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::tuple_gens&lt; 0, S... &gt;</class>
    <class kind="struct">boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::tuple_seq</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::pop_front_impl&lt; atria::meta::pack_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1pop__front__impl_3_01atria_1_1meta_1_1pack__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::pop_front_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::pop_front_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; First, Types... &gt; &gt;</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::pop_front_impl&lt; atria::meta::std_tuple_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1pop__front__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::pop_front_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::pop_front_impl&lt; atria::meta::std_tuple_tag &gt;::apply&lt; std::tuple&lt; First, Types... &gt; &gt;</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::push_back_impl&lt; atria::meta::pack_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1push__back__impl_3_01atria_1_1meta_1_1pack__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::push_back_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::push_back_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; Args... &gt;, T &gt;</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::push_back_impl&lt; atria::meta::std_tuple_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1push__back__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::push_back_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::push_back_impl&lt; atria::meta::std_tuple_tag &gt;::apply&lt; std::tuple&lt; Args... &gt;, T &gt;</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::push_front_impl&lt; atria::meta::pack_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1push__front__impl_3_01atria_1_1meta_1_1pack__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::push_front_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::push_front_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; Args... &gt;, T &gt;</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::push_front_impl&lt; atria::meta::std_tuple_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1push__front__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::push_front_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::push_front_impl&lt; atria::meta::std_tuple_tag &gt;::apply&lt; std::tuple&lt; Args... &gt;, T &gt;</class>
  </compound>
  <compound kind="struct">
    <name>atria::xform::impure::reduce_aborted_error</name>
    <filename>structatria_1_1xform_1_1impure_1_1reduce__aborted__error.html</filename>
    <templarg></templarg>
    <base>atria::xform::impure::reduce_aborted_error_base</base>
  </compound>
  <compound kind="struct">
    <name>atria::xform::impure::reduce_aborted_error_base</name>
    <filename>structatria_1_1xform_1_1impure_1_1reduce__aborted__error__base.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::xform::reductor_fn</name>
    <filename>structatria_1_1xform_1_1reductor__fn.html</filename>
    <templarg>ReducingFnT</templarg>
    <templarg>InitialStateT</templarg>
    <templarg>InputTs</templarg>
    <base>reductor_fn_base&lt; ReducingFnT, estd::result_of_t&lt; ReducingFnT(InitialStateT, InputTs...)&gt;, InputTs... &gt;</base>
  </compound>
  <compound kind="struct">
    <name>atria::xform::reductor_fn_base</name>
    <filename>structatria_1_1xform_1_1reductor__fn__base.html</filename>
    <templarg>ReducingFnT</templarg>
    <templarg>StateT</templarg>
    <templarg>InputTs</templarg>
    <member kind="function">
      <type></type>
      <name>operator bool</name>
      <anchorfile>structatria_1_1xform_1_1reductor__fn__base.html</anchorfile>
      <anchor>aa385aa18f5e42db5a415c25a90f4193d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>complete_type</type>
      <name>complete</name>
      <anchorfile>structatria_1_1xform_1_1reductor__fn__base.html</anchorfile>
      <anchor>a87719260e4e46aee899b3e9a39c47fd3</anchor>
      <arglist>() const &amp;</arglist>
    </member>
    <member kind="function">
      <type>complete_type</type>
      <name>current</name>
      <anchorfile>structatria_1_1xform_1_1reductor__fn__base.html</anchorfile>
      <anchor>aa989a52376a17bfd48d1da22da7aa0fb</anchor>
      <arglist>() const &amp;</arglist>
    </member>
    <member kind="function">
      <type>reductor_fn_base &amp;</type>
      <name>operator()</name>
      <anchorfile>structatria_1_1xform_1_1reductor__fn__base.html</anchorfile>
      <anchor>a718625045dbe306bb5a5a1d49ede8bd4</anchor>
      <arglist>(InputTs2 &amp;&amp;...ins)&amp;</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>reductor_fn_base&lt; detail::caller&lt; estd::decay_t&lt; ReducingFnT &gt; &gt;, estd::decay_t&lt; skip_result_t&lt; ReducingFnT, InitialStateT, InputTs... &gt; &gt;, InputTs... &gt;</name>
    <filename>structatria_1_1xform_1_1reductor__fn__base.html</filename>
  </compound>
  <compound kind="class">
    <name>reductor_fn_base&lt; ReducingFnT, estd::result_of_t&lt; ReducingFnT(InitialStateT, InputTs...)&gt;, InputTs... &gt;</name>
    <filename>structatria_1_1xform_1_1reductor__fn__base.html</filename>
    <member kind="function">
      <type></type>
      <name>operator bool</name>
      <anchorfile>structatria_1_1xform_1_1reductor__fn__base.html</anchorfile>
      <anchor>aa385aa18f5e42db5a415c25a90f4193d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>complete_type</type>
      <name>complete</name>
      <anchorfile>structatria_1_1xform_1_1reductor__fn__base.html</anchorfile>
      <anchor>a87719260e4e46aee899b3e9a39c47fd3</anchor>
      <arglist>() const &amp;</arglist>
    </member>
    <member kind="function">
      <type>complete_type</type>
      <name>current</name>
      <anchorfile>structatria_1_1xform_1_1reductor__fn__base.html</anchorfile>
      <anchor>aa989a52376a17bfd48d1da22da7aa0fb</anchor>
      <arglist>() const &amp;</arglist>
    </member>
    <member kind="function">
      <type>reductor_fn_base &amp;</type>
      <name>operator()</name>
      <anchorfile>structatria_1_1xform_1_1reductor__fn__base.html</anchorfile>
      <anchor>a718625045dbe306bb5a5a1d49ede8bd4</anchor>
      <arglist>(InputTs2 &amp;&amp;...ins)&amp;</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>atria::xform::result_of</name>
    <filename>structatria_1_1xform_1_1result__of.html</filename>
    <templarg></templarg>
    <templarg>InputTs</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::xform::result_of&lt; XformT, meta::pack&lt; InputTs... &gt; &gt;</name>
    <filename>structatria_1_1xform_1_1result__of_3_01_xform_t_00_01meta_1_1pack_3_01_input_ts_8_8_8_01_4_01_4.html</filename>
    <templarg></templarg>
    <templarg>InputTs</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::testing::mocks::returning</name>
    <filename>structatria_1_1testing_1_1mocks_1_1returning.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>atria::funken::sensor</name>
    <filename>classatria_1_1funken_1_1sensor.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::xform::sequence_range</name>
    <filename>structatria_1_1xform_1_1sequence__range.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg>RangeTs</templarg>
    <class kind="struct">atria::xform::sequence_range::iterator</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::sequence_tag&lt; atria::meta::pack&lt; Args... &gt; &gt;</name>
    <filename>structboost_1_1mpl_1_1sequence__tag_3_01atria_1_1meta_1_1pack_3_01_args_8_8_8_01_4_01_4.html</filename>
    <templarg>Args</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::sequence_tag&lt; std::tuple&lt; Args... &gt; &gt;</name>
    <filename>structboost_1_1mpl_1_1sequence__tag_3_01std_1_1tuple_3_01_args_8_8_8_01_4_01_4.html</filename>
    <templarg>Args</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::size_impl&lt; atria::meta::pack_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1size__impl_3_01atria_1_1meta_1_1pack__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::size_impl&lt; atria::meta::pack_tag &gt;::apply</class>
    <class kind="struct">boost::mpl::size_impl&lt; atria::meta::pack_tag &gt;::apply&lt; atria::meta::pack&lt; Ts... &gt; &gt;</class>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::size_impl&lt; atria::meta::std_tuple_tag &gt;</name>
    <filename>structboost_1_1mpl_1_1size__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4.html</filename>
    <class kind="struct">boost::mpl::size_impl&lt; atria::meta::std_tuple_tag &gt;::apply</class>
  </compound>
  <compound kind="struct">
    <name>atria::xform::skip_result</name>
    <filename>structatria_1_1xform_1_1skip__result.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg>InputTs</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::xform::skip_state</name>
    <filename>structatria_1_1xform_1_1skip__state.html</filename>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>atria::testing::spy_fn</name>
    <filename>classatria_1_1testing_1_1spy__fn.html</filename>
    <templarg>MockT</templarg>
  </compound>
  <compound kind="class">
    <name>atria::funken::state</name>
    <filename>classatria_1_1funken_1_1state.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::xform::state_traits</name>
    <filename>structatria_1_1xform_1_1state__traits.html</filename>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static auto</type>
      <name>is_reduced</name>
      <anchorfile>structatria_1_1xform_1_1state__traits.html</anchorfile>
      <anchor>a29eb8899ba5e0c2e266c285042e67ebe</anchor>
      <arglist>(T &amp;&amp;) -&gt; bool        </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static auto</type>
      <name>data</name>
      <anchorfile>structatria_1_1xform_1_1state__traits.html</anchorfile>
      <anchor>ac09e5ef6d0902f21a633c3b7105e95ef</anchor>
      <arglist>(T &amp;&amp;, D &amp;&amp;d) -&gt; decltype(std::forward&lt; D &gt;(d)())</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static auto</type>
      <name>complete</name>
      <anchorfile>structatria_1_1xform_1_1state__traits.html</anchorfile>
      <anchor>a18456c946a84c9b57eb4e0bd2732024a</anchor>
      <arglist>(T &amp;&amp;state) -&gt; decltype(std::forward&lt; T &gt;(state))</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static auto</type>
      <name>unwrap</name>
      <anchorfile>structatria_1_1xform_1_1state__traits.html</anchorfile>
      <anchor>a7a61e1d47a98a6262eeb5d3c1dc17a89</anchor>
      <arglist>(T &amp;&amp;state) -&gt; decltype(std::forward&lt; T &gt;(state))</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static auto</type>
      <name>unwrap_all</name>
      <anchorfile>structatria_1_1xform_1_1state__traits.html</anchorfile>
      <anchor>ab28ded51695652beb897602b1760c341</anchor>
      <arglist>(T &amp;&amp;state) -&gt; decltype(std::forward&lt; T &gt;(state))</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static auto</type>
      <name>rewrap</name>
      <anchorfile>structatria_1_1xform_1_1state__traits.html</anchorfile>
      <anchor>a0859a028d9d963bc95e583b70b938233</anchor>
      <arglist>(T &amp;&amp;, U &amp;&amp;x) -&gt; decltype(std::forward&lt; U &gt;(x))</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>atria::xform::state_traits&lt; any_state &gt;</name>
    <filename>structatria_1_1xform_1_1state__traits_3_01any__state_01_4.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::xform::state_traits&lt; skip_state&lt; SkippedT, CalledT &gt; &gt;</name>
    <filename>structatria_1_1xform_1_1state__traits_3_01skip__state_3_01_skipped_t_00_01_called_t_01_4_01_4.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <class kind="struct">atria::xform::state_traits&lt; skip_state&lt; SkippedT, CalledT &gt; &gt;::can_not_do_that</class>
  </compound>
  <compound kind="struct">
    <name>atria::xform::state_traits&lt; state_wrapper&lt; TagT, StateT, DataT &gt; &gt;</name>
    <filename>structatria_1_1xform_1_1state__traits_3_01state__wrapper_3_01_tag_t_00_01_state_t_00_01_data_t_01_4_01_4.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::xform::state_wrapper</name>
    <filename>structatria_1_1xform_1_1state__wrapper.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::std_tuple_iterator</name>
    <filename>structatria_1_1meta_1_1std__tuple__iterator.html</filename>
    <templarg>Args</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::meta::std_tuple_iterator&lt; std::tuple&lt; Args... &gt; &gt;</name>
    <filename>structatria_1_1meta_1_1std__tuple__iterator_3_01std_1_1tuple_3_01_args_8_8_8_01_4_01_4.html</filename>
    <templarg>Args</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::funken::structure</name>
    <filename>structatria_1_1funken_1_1structure.html</filename>
    <templarg>T</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::prelude::tracer</name>
    <filename>structatria_1_1prelude_1_1tracer.html</filename>
  </compound>
  <compound kind="struct">
    <name>atria::xform::transducer_impl</name>
    <filename>structatria_1_1xform_1_1transducer__impl.html</filename>
    <templarg>ReducingFnGenT</templarg>
    <templarg>ParamTs</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::tuple_gens</name>
    <filename>structboost_1_1mpl_1_1pop__back__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1tuple__gens.html</filename>
    <templarg>N</templarg>
    <templarg>S</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::tuple_gens&lt; 0, S... &gt;</name>
    <filename>structboost_1_1mpl_1_1pop__back__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1tuple__gens_3_010_00_01_s_8_8_8_01_4.html</filename>
    <templarg>S</templarg>
  </compound>
  <compound kind="struct">
    <name>boost::mpl::pop_back_impl&lt; atria::meta::std_tuple_tag &gt;::tuple_seq</name>
    <filename>structboost_1_1mpl_1_1pop__back__impl_3_01atria_1_1meta_1_1std__tuple__tag_01_4_1_1tuple__seq.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::prelude::tuplify_t</name>
    <filename>structatria_1_1prelude_1_1tuplify__t.html</filename>
  </compound>
  <compound kind="class">
    <name>atria::testing::variant_spy</name>
    <filename>classatria_1_1testing_1_1variant__spy.html</filename>
    <class kind="struct">atria::testing::variant_spy::all_variants</class>
  </compound>
  <compound kind="struct">
    <name>atria::variant::variant_types</name>
    <filename>structatria_1_1variant_1_1variant__types.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::variant::variant_types_impl</name>
    <filename>structatria_1_1variant_1_1variant__types__impl.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>atria::variant::variant_types_impl&lt; boost::variant&lt; T, Ts... &gt; &gt;</name>
    <filename>structatria_1_1variant_1_1variant__types__impl_3_01boost_1_1variant_3_01_t_00_01_ts_8_8_8_01_4_01_4.html</filename>
    <templarg></templarg>
    <templarg>Ts</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::variant::variant_types_impl&lt; eggs::variants::variant&lt; Ts... &gt; &gt;</name>
    <filename>structatria_1_1variant_1_1variant__types__impl_3_01eggs_1_1variants_1_1variant_3_01_ts_8_8_8_01_4_01_4.html</filename>
    <templarg>Ts</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::variant::variant_types_impl&lt; meta::pack&lt; Ts... &gt; &gt;</name>
    <filename>structatria_1_1variant_1_1variant__types__impl_3_01meta_1_1pack_3_01_ts_8_8_8_01_4_01_4.html</filename>
    <templarg>Ts</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::variant::visitor_result_of</name>
    <filename>structatria_1_1variant_1_1visitor__result__of.html</filename>
    <templarg>FnT</templarg>
    <templarg>VariantTs</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::variant::visitor_result_of&lt; FnT, meta::pack&lt; VariantTs... &gt; &gt;</name>
    <filename>structatria_1_1variant_1_1visitor__result__of_3_01_fn_t_00_01meta_1_1pack_3_01_variant_ts_8_8_8_01_4_01_4.html</filename>
    <templarg></templarg>
    <templarg>VariantTs</templarg>
    <base>visitor_result_of&lt; FnT, VariantTs... &gt;</base>
  </compound>
  <compound kind="class">
    <name>visitor_result_of&lt; FnT, VariantTs... &gt;</name>
    <filename>structatria_1_1variant_1_1visitor__result__of.html</filename>
  </compound>
  <compound kind="class">
    <name>atria::variant::visitor_t</name>
    <filename>classatria_1_1variant_1_1visitor__t.html</filename>
    <templarg></templarg>
    <templarg>Fns</templarg>
  </compound>
  <compound kind="struct">
    <name>atria::variant::when_t</name>
    <filename>structatria_1_1variant_1_1when__t.html</filename>
    <templarg></templarg>
    <templarg>Args</templarg>
  </compound>
  <compound kind="namespace">
    <name>atria</name>
    <filename>namespaceatria.html</filename>
    <namespace>atria::estd</namespace>
    <namespace>atria::funken</namespace>
    <namespace>atria::meta</namespace>
    <namespace>atria::prelude</namespace>
    <namespace>atria::testing</namespace>
    <namespace>atria::variant</namespace>
    <namespace>atria::xform</namespace>
  </compound>
  <compound kind="namespace">
    <name>atria::estd</name>
    <filename>namespaceatria_1_1estd.html</filename>
    <class kind="struct">atria::estd::integer_sequence</class>
    <class kind="struct">atria::estd::nonesuch</class>
    <member kind="typedef">
      <type>typename detail::make_void&lt; Ts... &gt;::type</type>
      <name>void_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>adbf75a4cd9d4bd42ac66686f1125821a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::decay&lt; T &gt;::type</type>
      <name>decay_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>abccbc22bdad41d01de217a42e0d077ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::result_of&lt; T &gt;::type</type>
      <name>result_of_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>abf1c2986a71eebc351b3b2b01cc442e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::conditional&lt; X, T, F &gt;::type</type>
      <name>conditional_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>a7e8ac30440b9ec3fef45a9172f1f43f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::remove_reference&lt; T &gt;::type</type>
      <name>remove_reference_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>a3a08cea569e6926ac8d7d74dd7178b5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::remove_const&lt; T &gt;::type</type>
      <name>remove_const_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>a31ee6e9231fa50c7fdd7292f0c45f13e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::enable_if&lt; X, T &gt;::type</type>
      <name>enable_if_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>a3d7e0f60f8c349b2a05f1fcf56750360</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename detail::detector&lt; nonesuch, void, Op, Args... &gt;::value_t</type>
      <name>is_detected</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>a16a19bd6407910d9725dcd05536f5901</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename detail::detector&lt; nonesuch, void, Op, Args... &gt;::type</type>
      <name>detected_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>aeddaa6436b2284bf4bc0c4620a2ded33</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>detail::detector&lt; Default, void, Op, Args... &gt;</type>
      <name>detected_or</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>a0db8e3a48df40f65b7946b4db63747eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename detected_or&lt; Default, Op, Args... &gt;::type</type>
      <name>detected_or_t</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>a80f94c5a0b73ffc291247f406ee7e3b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::is_same&lt; Expected, detected_t&lt; Op, Args... &gt; &gt;</type>
      <name>is_detected_exact</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>a54efded7d5471a1b8d88f5c2422a767e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::is_convertible&lt; detected_t&lt; Op, Args... &gt;, To &gt;</type>
      <name>is_detected_convertible</name>
      <anchorfile>namespaceatria_1_1estd.html</anchorfile>
      <anchor>ac286f275998780a3a3ce9fe2795db6aa</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>atria::funken</name>
    <filename>namespaceatria_1_1funken.html</filename>
    <class kind="class">atria::funken::inoutput</class>
    <class kind="class">atria::funken::input</class>
    <class kind="struct">atria::funken::no_value_error</class>
    <class kind="class">atria::funken::output</class>
    <class kind="class">atria::funken::sensor</class>
    <class kind="class">atria::funken::state</class>
    <class kind="struct">atria::funken::structure</class>
    <member kind="function">
      <type></type>
      <name>ABL_CONCEPT_SPEC</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a1397595b0f7785bf65ba657255da83fc</anchor>
      <arglist>(In_value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ABL_CONCEPT_SPEC</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a5303cbcb73a924b458ee098e3ee860c9</anchor>
      <arglist>(Out_value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ABL_CONCEPT_SPEC</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>af84b9510943cdbf07d6ecb038961df9c</anchor>
      <arglist>(Inout_value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ABL_CONCEPT_SPEC</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a30cbff4de15a4a6c2904097da49d7a69</anchor>
      <arglist>(Root_value)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>in</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>ae31a5ffbac61510c6080d6b4c3bc753d</anchor>
      <arglist>(InT &amp;&amp;object) -&gt; estd::enable_if_t&lt;              (In_value&lt; InT &gt;()),           detail::input_impl&lt; detail::signal_type_t&lt; InT &gt; &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>inout</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a3d4e799f1a23b57de707a04e33ca193f</anchor>
      <arglist>(InoutT &amp;&amp;object) -&gt; estd::enable_if_t&lt;              (Inout_value&lt; InoutT &gt;()),           detail::inoutput_impl&lt; detail::signal_type_t&lt; InoutT &gt; &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>out</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a8fa6c1b4a04d300807da8ba38beb175e</anchor>
      <arglist>(OutT &amp;&amp;object) -&gt; estd::enable_if_t&lt;              (Out_value&lt; OutT &gt;()),           detail::output_impl&lt; detail::signal_type_t&lt; OutT &gt; &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>modified</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a33481a7baa80556faa4670ea386ea5a7</anchor>
      <arglist>(T &amp;) -&gt; estd::enable_if_t&lt;!std::is_convertible&lt; T &amp;, structure&lt; T &gt; &amp; &gt;::value &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>xformed</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>ae40b89f6247ee361fd7ba4265f70df72</anchor>
      <arglist>(Xform &amp;&amp;xform, InTs &amp;&amp;...ins) -&gt; estd::enable_if_t&lt;              meta::all(In_value&lt; InTs &gt;()...),           detail::xformed_input&lt;                      typename decltype(                           detail::make_xform_down_signal(                                   xform, detail::access::signal(ins)...)                           )::element_type                   &gt;           &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>xat</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a07d46d69e56e39495628078c7a334b83</anchor>
      <arglist>(KeyT &amp;&amp;key) -&gt; xform::transducer_impl&lt; detail::at_rf_gen, estd::decay_t&lt; KeyT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>uat</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a8ebd860c57ce91e0aa60a0f1eb28b1d0</anchor>
      <arglist>(KeyT &amp;&amp;key) -&gt; detail::at_updater&lt; estd::decay_t&lt; KeyT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>atted</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>afed87db53d811270ec18f3d92b769e9c</anchor>
      <arglist>(KeyT &amp;&amp;k, Ins &amp;&amp;...ins) -&gt; estd::enable_if_t&lt;              meta::all(In_value&lt; Ins &gt;()&amp;&amp;!Out_value&lt; Ins &gt;()...),           decltype(xformed(xat(k), ins...))           &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>get_attr</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a90dd7256b896c1025a5fa9c555f1213e</anchor>
      <arglist>(AttrPtrT p) -&gt; detail::get_attr_fn&lt; AttrPtrT &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>set_attr</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>a147be8a16f2874a61045fd9a6da63af1</anchor>
      <arglist>(AttrPtrT p) -&gt; detail::set_attr_fn&lt; AttrPtrT &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>attred</name>
      <anchorfile>namespaceatria_1_1funken.html</anchorfile>
      <anchor>aba2e0bc257a375e095eb096264dc5335</anchor>
      <arglist>(AttrPtrT attr, Ins &amp;&amp;...ins) -&gt; estd::enable_if_t&lt;              meta::all(In_value&lt; Ins &gt;()&amp;&amp;!Out_value&lt; Ins &gt;()...),                                   decltype(xformed(xform::map(get_attr(attr)), ins...))           &gt;</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>atria::meta</name>
    <filename>namespaceatria_1_1meta.html</filename>
    <class kind="struct">atria::meta::bottom</class>
    <class kind="struct">atria::meta::common_type</class>
    <class kind="struct">atria::meta::common_type&lt; T, Ts... &gt;</class>
    <class kind="struct">atria::meta::common_type&lt;&gt;</class>
    <class kind="struct">atria::meta::copy_cv</class>
    <class kind="struct">atria::meta::copy_decay</class>
    <class kind="struct">atria::meta::copy_reference</class>
    <class kind="struct">atria::meta::copy_trait</class>
    <class kind="struct">atria::meta::could_not_find_common_type</class>
    <class kind="struct">atria::meta::could_not_get_index_sequence</class>
    <class kind="struct">atria::meta::detected_any</class>
    <class kind="struct">atria::meta::detected_any&lt; T, Op &gt;</class>
    <class kind="struct">atria::meta::detected_any&lt; T, Op, Ops... &gt;</class>
    <class kind="struct">atria::meta::from_void</class>
    <class kind="struct">atria::meta::get_value_type</class>
    <class kind="struct">atria::meta::identity</class>
    <class kind="struct">atria::meta::if_any</class>
    <class kind="struct">atria::meta::if_any&lt; T, Mf &gt;</class>
    <class kind="struct">atria::meta::if_any&lt; T, Mf, Mfs... &gt;</class>
    <class kind="struct">atria::meta::lazy_detected_or</class>
    <class kind="struct">atria::meta::lazy_enable_if</class>
    <class kind="struct">atria::meta::models</class>
    <class kind="struct">atria::meta::models&lt;                  ConceptSpecT(Ts...),           estd::void_t&lt;                                                  decltype(std::declval&lt; ConceptSpecT &gt;().requires_(                                                                                                                                   std::declval&lt; Ts &gt;()...))                           &gt;           &gt;</class>
    <class kind="struct">atria::meta::models_</class>
    <class kind="struct">atria::meta::noop_t</class>
    <class kind="struct">atria::meta::pack</class>
    <class kind="struct">atria::meta::pack_iterator</class>
    <class kind="struct">atria::meta::pack_iterator&lt; atria::meta::pack&lt; Args... &gt; &gt;</class>
    <class kind="struct">atria::meta::std_tuple_iterator</class>
    <class kind="struct">atria::meta::std_tuple_iterator&lt; std::tuple&lt; Args... &gt; &gt;</class>
    <member kind="typedef">
      <type>typename common_type&lt; Ts... &gt;::type</type>
      <name>common_type_t</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>aba0e22763ba45cf3edf22f604e5ed3ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>estd::enable_if_t&lt; Requirement, int &gt;</type>
      <name>require</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>acecee0f2f55cb61c7c134944be4d7df1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>estd::enable_if_t&lt; if_any&lt; T, Mfs... &gt;::type::value, int &gt;</type>
      <name>require_any</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>af13ec4b3c9557f037c62921d71fbbfeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename T::type</type>
      <name>eval_t</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>a077a87021cba858ea8d36b0e1d59f902</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename detail::unpack&lt; MF, T &gt;::type</type>
      <name>unpack</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>a11375eeae94b43372dd0f70a867f200f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>eval_t&lt; get_value_type&lt; estd::decay_t&lt; T &gt; &gt; &gt;</type>
      <name>value_t</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>a5dcf93ca18529def3acf809f9e15c67f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>all</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>aa4981af4f6de6abc3ecf131454b9e1fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>valid</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>a9e425a1c7a59fc570b8968a2a975c006</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>expressions</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>a15afd0609516e21f990bbcc5b4f69708</anchor>
      <arglist>(Ts &amp;&amp;...)</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>check</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>adf7033d67a82ad70d515d189a054fe2f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>operator==</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>afed7f8e3e576f161e31bc472440ee98d</anchor>
      <arglist>(const pack&lt; Ts1... &gt; &amp;, const pack&lt; Ts2... &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>operator!=</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>a944e22221a11965e834bb5ca7116d988</anchor>
      <arglist>(const pack&lt; Ts1... &gt; &amp;, const pack&lt; Ts2... &gt; &amp;)</arglist>
    </member>
    <member kind="variable">
      <type>constexpr int</type>
      <name>can_be_void</name>
      <anchorfile>namespaceatria_1_1meta.html</anchorfile>
      <anchor>a3ea3b7864ce402cf4a3060ccea7502f3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>atria::prelude</name>
    <filename>namespaceatria_1_1prelude.html</filename>
    <class kind="struct">atria::prelude::complement_t</class>
    <class kind="struct">atria::prelude::constantly_t</class>
    <class kind="struct">atria::prelude::identity_t</class>
    <class kind="struct">atria::prelude::identity_t_</class>
    <class kind="struct">atria::prelude::tracer</class>
    <class kind="struct">atria::prelude::tuplify_t</class>
    <member kind="function">
      <type>auto</type>
      <name>comp</name>
      <anchorfile>namespaceatria_1_1prelude.html</anchorfile>
      <anchor>a76571986e0dbf8a149a1ae55ede5bfde</anchor>
      <arglist>(F &amp;&amp;f) -&gt; F &amp;&amp;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>complement</name>
      <anchorfile>namespaceatria_1_1prelude.html</anchorfile>
      <anchor>a7458009df9fab4d7899bbda48dd9713d</anchor>
      <arglist>(FnT &amp;&amp;fn) -&gt; complement_t&lt; estd::decay_t&lt; FnT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>constantly</name>
      <anchorfile>namespaceatria_1_1prelude.html</anchorfile>
      <anchor>ae84f7a055fedf797752abfb80f34ae90</anchor>
      <arglist>(T &amp;&amp;value) -&gt; constantly_t&lt; estd::decay_t&lt; T &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>trace</name>
      <anchorfile>namespaceatria_1_1prelude.html</anchorfile>
      <anchor>a727c15b2eda2a38e3a7f526349950c22</anchor>
      <arglist>(T &amp;&amp;x, const std::string &amp;message) -&gt; T &amp;&amp;</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>atria::testing</name>
    <filename>namespaceatria_1_1testing.html</filename>
    <class kind="class">atria::testing::benchmark_runner</class>
    <class kind="struct">atria::testing::benchmark_runner_error</class>
    <class kind="struct">atria::testing::benchmark_settings</class>
    <class kind="class">atria::testing::benchmark_suite</class>
    <class kind="class">atria::testing::benchmark_suite&lt; void &gt;</class>
    <class kind="struct">atria::testing::copy_spy</class>
    <class kind="class">atria::testing::spy_fn</class>
    <class kind="class">atria::testing::variant_spy</class>
    <member kind="function">
      <type>void</type>
      <name>unoptimize</name>
      <anchorfile>namespaceatria_1_1testing.html</anchorfile>
      <anchor>acd42111d8fcc94dd7fad31a3af055fa7</anchor>
      <arglist>(const void *)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>timeit</name>
      <anchorfile>namespaceatria_1_1testing.html</anchorfile>
      <anchor>a10ed11e83a2e5e54e8eb4b7b003b11d8</anchor>
      <arglist>(FnT &amp;&amp;fn) -&gt; std::chrono::duration&lt; double, std::milli &gt;</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>benchmark_main</name>
      <anchorfile>namespaceatria_1_1testing.html</anchorfile>
      <anchor>a163ec995e873324e3c8c33396e0e799c</anchor>
      <arglist>(int argc, char const *const *argv, FnT &amp;&amp;fn)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>spy</name>
      <anchorfile>namespaceatria_1_1testing.html</anchorfile>
      <anchor>a1d690a15d59c27d0f80b28111e85daff</anchor>
      <arglist>(const Fn &amp;fn) -&gt; spy_fn&lt; Fn &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>spy</name>
      <anchorfile>namespaceatria_1_1testing.html</anchorfile>
      <anchor>a728ac676e31248bae49df08233279457</anchor>
      <arglist>() -&gt; spy_fn&lt;&gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>spy_on</name>
      <anchorfile>namespaceatria_1_1testing.html</anchorfile>
      <anchor>a131ae9a05d71f92e0f898404c74dcbb1</anchor>
      <arglist>(MockT &amp;mock) -&gt; spy_fn&lt; detail::scoped_intruder&lt; MockT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>spy_on</name>
      <anchorfile>namespaceatria_1_1testing.html</anchorfile>
      <anchor>a76b48581275e46d9c3745772a1a148b1</anchor>
      <arglist>(MockT &amp;mock, const FnT &amp;replacement) -&gt; spy_fn&lt; detail::scoped_intruder&lt; MockT &gt; &gt;</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>atria::variant</name>
    <filename>namespaceatria_1_1variant.html</filename>
    <class kind="struct">atria::variant::otherwise_t</class>
    <class kind="struct">atria::variant::variant_types</class>
    <class kind="struct">atria::variant::variant_types_impl</class>
    <class kind="struct">atria::variant::variant_types_impl&lt; boost::variant&lt; T, Ts... &gt; &gt;</class>
    <class kind="struct">atria::variant::variant_types_impl&lt; eggs::variants::variant&lt; Ts... &gt; &gt;</class>
    <class kind="struct">atria::variant::variant_types_impl&lt; meta::pack&lt; Ts... &gt; &gt;</class>
    <class kind="struct">atria::variant::visitor_result_of</class>
    <class kind="struct">atria::variant::visitor_result_of&lt; FnT, meta::pack&lt; VariantTs... &gt; &gt;</class>
    <class kind="class">atria::variant::visitor_t</class>
    <class kind="struct">atria::variant::when_t</class>
    <member kind="function">
      <type>auto</type>
      <name>match</name>
      <anchorfile>namespaceatria_1_1variant.html</anchorfile>
      <anchor>a26f1198672773eafb32564299c7ed575</anchor>
      <arglist>(VariantT &amp;variant, FnTs &amp;&amp;...fns) -&gt; estd::enable_if_t&lt;      detail::is_boost_variant&lt; estd::decay_t&lt; VariantT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>match</name>
      <anchorfile>namespaceatria_1_1variant.html</anchorfile>
      <anchor>a805602a61739301616b7a4eca1fd42c0</anchor>
      <arglist>(VariantT &amp;&amp;variant, FnTs &amp;&amp;...fns) -&gt; estd::enable_if_t&lt;      detail::is_eggs_variant&lt; estd::decay_t&lt; VariantT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>when_t&lt; Fn, typename boost::mpl::if_&lt; std::is_reference&lt; Args &gt;, Args, const Args &amp; &gt;::type... &gt;</type>
      <name>when</name>
      <anchorfile>namespaceatria_1_1variant.html</anchorfile>
      <anchor>ab60ccb4829cc97083de66d8a36bf1bdd</anchor>
      <arglist>(Fn &amp;&amp;fn)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>visitor</name>
      <anchorfile>namespaceatria_1_1variant.html</anchorfile>
      <anchor>a1fd6a365e6153690733db03820dd1984</anchor>
      <arglist>(FnTs &amp;&amp;...fns) -&gt; visitor_t&lt;              meta::common_type_t&lt;                      typename std::result_of&lt; FnTs(meta::bottom)&gt;::type... &gt;,           FnTs... &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>visitor_for</name>
      <anchorfile>namespaceatria_1_1variant.html</anchorfile>
      <anchor>adf7c7bfe6f794ce07243e09c95dd59bb</anchor>
      <arglist>(FnTs &amp;&amp;...fns) -&gt; visitor_t&lt;              visitor_result_of_t&lt;                      detail::visitor_impl&lt; FnTs... &gt;,                   variant_types_t&lt; VariantT &gt; &gt;,           FnTs... &gt;</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>atria::xform</name>
    <filename>namespaceatria_1_1xform.html</filename>
    <class kind="class">atria::xform::any_state</class>
    <class kind="struct">atria::xform::emplace_back_rf_t</class>
    <class kind="struct">atria::xform::empty_reductor_fn</class>
    <class kind="struct">atria::xform::empty_reductor_fn&lt; ReducingFnT, InitialStateT, meta::pack&lt; InputTs... &gt; &gt;</class>
    <class kind="struct">atria::xform::first_rf_t</class>
    <class kind="struct">atria::xform::is_skip_state</class>
    <class kind="struct">atria::xform::is_skip_state&lt; skip_state&lt; SkippedT, CalledT &gt; &gt;</class>
    <class kind="struct">atria::xform::is_state_wrapper</class>
    <class kind="struct">atria::xform::is_state_wrapper&lt; _, state_wrapper&lt; T, S, D &gt; &gt;</class>
    <class kind="struct">atria::xform::last_rf_t</class>
    <class kind="struct">atria::xform::maybe_reduced_tag</class>
    <class kind="struct">atria::xform::no_tag</class>
    <class kind="struct">atria::xform::output_of</class>
    <class kind="struct">atria::xform::output_of&lt; XformT, meta::pack&lt; InputTs... &gt; &gt;</class>
    <class kind="struct">atria::xform::output_rf_t</class>
    <class kind="struct">atria::xform::reductor_fn</class>
    <class kind="struct">atria::xform::reductor_fn_base</class>
    <class kind="struct">atria::xform::result_of</class>
    <class kind="struct">atria::xform::result_of&lt; XformT, meta::pack&lt; InputTs... &gt; &gt;</class>
    <class kind="struct">atria::xform::sequence_range</class>
    <class kind="struct">atria::xform::skip_result</class>
    <class kind="struct">atria::xform::skip_state</class>
    <class kind="struct">atria::xform::state_traits</class>
    <class kind="struct">atria::xform::state_traits&lt; any_state &gt;</class>
    <class kind="struct">atria::xform::state_traits&lt; skip_state&lt; SkippedT, CalledT &gt; &gt;</class>
    <class kind="struct">atria::xform::state_traits&lt; state_wrapper&lt; TagT, StateT, DataT &gt; &gt;</class>
    <class kind="struct">atria::xform::state_wrapper</class>
    <class kind="struct">atria::xform::transducer_impl</class>
    <member kind="typedef">
      <type>state_wrapper&lt; maybe_reduced_tag, T, bool &gt;</type>
      <name>maybe_reduced</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>af2572203f7496bd93e991b7dbaa2772e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>transducer_impl&lt; meta::unpack&lt; detail::transducer_rf_gen, OutputT &gt;, detail::transducer_function_t&lt; InputT, OutputT &gt; &gt;</type>
      <name>transducer</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a12e4b8c9b4281bf93d4e649374f2d389</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ABL_CONCEPT_SPEC</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a6f09f6f468f00951f63d476cf3f200a2</anchor>
      <arglist>(State)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ABL_CONCEPT_SPEC</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a5d61103acf5e43b32458b61b4fb5c42f</anchor>
      <arglist>(Reducing_function)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ABL_CONCEPT_SPEC</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a80625416b5ebf0ce957cd1fd296ed80c</anchor>
      <arglist>(Transducer)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ABL_CONCEPT_SPEC</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ae50c949c55e49a934999f8724e805309</anchor>
      <arglist>(Transparent_transducer)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>into</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a8acde91bb38a74e8111d03f72f991470</anchor>
      <arglist>(CollectionT &amp;&amp;col, XformT &amp;&amp;xform, InputRangeTs &amp;&amp;...ranges) -&gt; CollectionT &amp;&amp;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>into_vector</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ad21b8bf7db847c2dd1ad4e426b938f85</anchor>
      <arglist>(XformT &amp;&amp;xform, InputRangeTs &amp;&amp;...ranges) -&gt; std::vector&lt; result_of_t&lt; XformT, meta::value_t&lt; InputRangeTs &gt;... &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>reduced_if</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a1cdbd85097477b77c5b4e744753e29b8</anchor>
      <arglist>(T &amp;&amp;x, bool is_reduced) -&gt; maybe_reduced&lt; estd::decay_t&lt; T &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>reduced</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a27b1401b1b47815969ff0867ad21f4e5</anchor>
      <arglist>(T &amp;&amp;x) -&gt; decltype(reduced_if(std::forward&lt; T &gt;(x), true))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>not_reduced</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a959ceb0a8362e3e5e4ef9f0a73a163c9</anchor>
      <arglist>(T &amp;&amp;x) -&gt; decltype(reduced_if(std::forward&lt; T &gt;(x), false))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>reduce</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a85da5e5fc0bf1b8b7ccf1eaf11b7fd80</anchor>
      <arglist>(ReducingFnT &amp;&amp;step, StateT &amp;&amp;state, InputRangeTs &amp;&amp;...ranges) -&gt; estd::decay_t&lt; StateT &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>reduce_nested</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>abd7d189e77566f74be8cbad8254ffb5a</anchor>
      <arglist>(ReducingFnT &amp;&amp;step, StateT &amp;&amp;state, InputRangeTs &amp;&amp;...ranges) -&gt; decltype(detail::is_non_empty(ranges...)                   ?call(detail::reduce_nested_non_empty_flipped,                                               std::forward&lt; StateT &gt;(state),                                               std::forward&lt; ReducingFnT &gt;(step),                                               std::forward&lt; InputRangeTs &gt;(ranges)...)                   :skip(std::forward&lt; StateT &gt;(state)))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>reductor</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a1e39dd603978c9a39ba6eaa5a64369b5</anchor>
      <arglist>(ReducingFnT &amp;&amp;step, InitialStateT &amp;&amp;state, InputTs &amp;&amp;...ins) -&gt; reductor_fn&lt; estd::decay_t&lt; ReducingFnT &gt;,                                                               estd::decay_t&lt; InitialStateT &gt;,                                                               estd::decay_t&lt; InputTs &gt;... &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>empty_reductor</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a4c47717f6c502f590dc15f173f264eae</anchor>
      <arglist>(ReducingFnT &amp;&amp;step, InitialStateT &amp;&amp;state) -&gt; empty_reductor_fn&lt; estd::decay_t&lt; ReducingFnT &gt;,                                                                                       estd::decay_t&lt; InitialStateT &gt;,                                                                                       estd::decay_t&lt; InputTs &gt;... &gt;</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>run</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a556bdf7d92cfc3f9678e478b2e0a7ac9</anchor>
      <arglist>(XformT &amp;&amp;xform, InputRangeTs &amp;&amp;...ranges)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>sequence</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>acaa64702270f0f9f1ebf7c1d4d9cf2eb</anchor>
      <arglist>(XformT &amp;&amp;xform, const RangeTs &amp;...ranges) -&gt; sequence_range&lt;              typename boost::mpl::eval_if&lt;                              std::is_same&lt; ValueT, detail::deduce_value_type &gt;,                           result_of&lt; XformT, meta::value_t&lt; RangeTs &gt;... &gt;,                           meta::identity&lt; ValueT &gt; &gt;::type,           estd::decay_t&lt; XformT &gt;,           estd::decay_t&lt; RangeTs &gt;... &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>skip</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a7b5d683f19ef370bc5e121c89f861c89</anchor>
      <arglist>(ReducingFnT &amp;&amp;, StateT &amp;&amp;state, InputTs &amp;&amp;...) -&gt; skip_result_t&lt; ReducingFnT, StateT, InputTs... &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>call</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a52fea8a48eaf32278634f831a495d251</anchor>
      <arglist>(ReducingFnT &amp;&amp;step, StateT &amp;&amp;state, InputTs &amp;&amp;...ins) -&gt; estd::enable_if_t&lt;              is_skip_state&lt; estd::decay_t&lt; StateT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_complete</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a742ad6e9cabc139c89bf66d8dc78c9ca</anchor>
      <arglist>(T &amp;&amp;s) -&gt; decltype(state_traits_t&lt; T &gt;::complete(std::forward&lt; T &gt;(s)))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_is_reduced</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>aa3bd5ac59b27e0db927043add4734650</anchor>
      <arglist>(T &amp;&amp;s) -&gt; bool</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_data</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a39ee97ff60db7e300fcdea53ae64b08d</anchor>
      <arglist>(T &amp;&amp;s, D &amp;&amp;d) -&gt; decltype(state_traits_t&lt; T &gt;::data(std::forward&lt; T &gt;(s),                                                                                                           std::forward&lt; D &gt;(d)))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_unwrap</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a8f3d5f97c45a219e65ba34cd3838e7ed</anchor>
      <arglist>(T &amp;&amp;s) -&gt; decltype(state_traits_t&lt; T &gt;::unwrap(std::forward&lt; T &gt;(s)))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_unwrap_all</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a4b8a06f0fe7f2e877ce00ebb20feac76</anchor>
      <arglist>(T &amp;&amp;s) -&gt; decltype(state_traits_t&lt; T &gt;::unwrap_all(std::forward&lt; T &gt;(s)))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_rewrap</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a6a2fb9067174fbd25ff78adaeb41650f</anchor>
      <arglist>(T &amp;&amp;s, U &amp;&amp;x) -&gt; decltype(state_traits_t&lt; T &gt;::rewrap(std::forward&lt; T &gt;(s), std::forward&lt; U &gt;(x)))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>wrap_state</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ad7b8b53c8727219bc6bbad59d8b58c1f</anchor>
      <arglist>(StateT &amp;&amp;next, DataT &amp;&amp;data=DataT{}) -&gt; state_wrapper&lt; TagT,                                                                       estd::decay_t&lt; StateT &gt;,                                                                       estd::decay_t&lt; DataT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_wrapper_complete</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a0e2b263b3e03295e68676c7df069f328</anchor>
      <arglist>(TagT, T &amp;&amp;s) -&gt; decltype(state_complete(state_unwrap(std::forward&lt; T &gt;(s))))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_wrapper_unwrap</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a0a1356003e10762cec1b6e68b4676ee8</anchor>
      <arglist>(TagT, T &amp;&amp;s) -&gt; decltype(std::get&lt; 0 &gt;(std::forward&lt; T &gt;(s)))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_wrapper_unwrap_all</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ab9b5e75829c1fdfe3f57451bc70790b0</anchor>
      <arglist>(TagT, T &amp;&amp;s) -&gt; decltype(state_unwrap_all(state_unwrap(std::forward&lt; T &gt;(s))))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_wrapper_rewrap</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a9d6df5b2f73d5e586e2dbce9a44fe747</anchor>
      <arglist>(TagT, T &amp;&amp;s, U &amp;&amp;x) -&gt; decltype(wrap_state&lt; TagT &gt;(                   state_rewrap(state_unwrap(std::forward&lt; T &gt;(s)), x),                   state_wrapper_data(std::forward&lt; T &gt;(s))))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>state_wrapper_data</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a8100207fd3c7ddf71e629248b76a184b</anchor>
      <arglist>(TagT tag, T &amp;&amp;s, D &amp;&amp;) -&gt; decltype(state_wrapper_data(tag, std::forward&lt; T &gt;(s)))</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>state_wrapper_data_is_reduced</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>af74cc4a347fd2ad83c01a0c7c35292de</anchor>
      <arglist>(TagT, DataT &amp;&amp;)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>state_wrapper_is_reduced</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>aab2250f9477d337be124b73f3ad9d2c8</anchor>
      <arglist>(TagT tag, T &amp;&amp;s)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>transduce</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>aa3ddac4a321b0ab20393f47485e42a50</anchor>
      <arglist>(XformT &amp;&amp;xform, ReducingFnT &amp;&amp;step, StateT &amp;&amp;state, InputRangeTs &amp;&amp;...ranges) -&gt; estd::decay_t&lt; StateT &gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>chainr</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ad18c36bdd6e85b3a7f6584603386ec61</anchor>
      <arglist>(InputRangeT &amp;&amp;r) -&gt; chainr_t&lt; estd::decay_t&lt; InputRangeT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>chain</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ac2b85e8714c0aa88ddb6dcc59c3501e6</anchor>
      <arglist>(InputRangeTs &amp;&amp;...rs) -&gt; decltype(chainr(std::forward&lt; InputRangeTs &gt;(rs)...))</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>chainl</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a70d85a17047adedbda1892ac046e092d</anchor>
      <arglist>(InputRangeT &amp;&amp;r) -&gt; chainl_t&lt; estd::decay_t&lt; InputRangeT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>count</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a355c4a75a7b2d4a537ef915446b4e307</anchor>
      <arglist>(InitT init=InitT{0}, StepT step=StepT{1}) -&gt; count_t&lt; InitT, StepT &gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>cycle</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a6ca64e4188beed34b52a9ddc7e692bd5</anchor>
      <arglist>(InputRangeT &amp;&amp;r) -&gt; cycle_t&lt; estd::decay_t&lt; InputRangeT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>drop</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a01f108701be19ec8d379b9f6b0515e53</anchor>
      <arglist>(IntegralT &amp;&amp;n) -&gt; drop_t&lt; estd::decay_t&lt; IntegralT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>drop_while</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a38696dd462d8382acbb53035db399d75</anchor>
      <arglist>(PredicateT &amp;&amp;n) -&gt; drop_while_t&lt; estd::decay_t&lt; PredicateT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>each</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ae2bc188bb24ad7c3799ad8198cbeb3c9</anchor>
      <arglist>(ActionT &amp;&amp;action) -&gt; each_t&lt; estd::decay_t&lt; ActionT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>eager</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a2f58051c6b87fb2548954b6f9d744126</anchor>
      <arglist>(MappingT &amp;&amp;mapping) -&gt; eager_t&lt; estd::decay_t&lt; MappingT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>enumerate_from</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a8a075d51b9bc7bda8f0b27de56d38c33</anchor>
      <arglist>(IntegralT &amp;&amp;init) -&gt; enumerate_t&lt; estd::decay_t&lt; IntegralT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>filter</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a80ba27e99da8878464eb743b464c368e</anchor>
      <arglist>(PredicateT &amp;&amp;predicate) -&gt; filter_t&lt; estd::decay_t&lt; PredicateT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>interpose</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>aeaf09b40e364f41e2e0018926f5bf5ee</anchor>
      <arglist>(ValueTs &amp;&amp;...xs) -&gt; interpose_t&lt; estd::make_index_sequence&lt; sizeof...(ValueTs)&gt;,                                                               std::tuple&lt; estd::decay_t&lt; ValueTs &gt;... &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>iter</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>acfab0c45a5f548e9a839f2060a45da77</anchor>
      <arglist>(InputRangeT &amp;&amp;r) -&gt; iter_t&lt; estd::decay_t&lt; InputRangeT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>map</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a9f5d15acc0898885bc4386a7c9b41005</anchor>
      <arglist>(MappingT &amp;&amp;mapping) -&gt; map_t&lt; estd::decay_t&lt; MappingT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>map_indexed</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a9f02ae83038b034fafb27e2f284499f1</anchor>
      <arglist>(MappingT &amp;&amp;mapping) -&gt; decltype(comp(                   count(),                   map(std::forward&lt; MappingT &gt;(mapping))))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>mapcat</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a980d70b208be73e99b32bc073ec92412</anchor>
      <arglist>(MappingT &amp;&amp;mapping) -&gt; decltype(comp(                   cat,                   map(std::forward&lt; MappingT &gt;(mapping))))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>partition</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a83103216261e92d2147ce41252272f76</anchor>
      <arglist>(IntegralT &amp;&amp;n) -&gt; partition_t&lt; estd::decay_t&lt; IntegralT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>partition_by</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a89e3ff42b7cdfce00041ef5be8c89efc</anchor>
      <arglist>(MappingT &amp;&amp;mapping) -&gt; partition_by_t&lt; estd::decay_t&lt; MappingT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>product</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a4fa098e18370e4117e3ae707e280d2bb</anchor>
      <arglist>(InputRangeT &amp;&amp;r) -&gt; product_t&lt; estd::decay_t&lt; InputRangeT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>random_sample</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>abb6065c740d69641dc343d90814152b0</anchor>
      <arglist>(ProbabilityT prob, GeneratorT generator=GeneratorT{}) -&gt; decltype(filter(detail::random_sampler&lt; ProbabilityT, GeneratorT &gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>range</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a416bf0ab5631d3cb304f6fdd3db0789a</anchor>
      <arglist>(StopT &amp;&amp;stop) -&gt; decltype(comp(                   count(),                   take(std::forward&lt; StopT &gt;(stop))))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>read</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a433828f060fdc4d07dcd50c9486833af</anchor>
      <arglist>(InputStreamT &amp;stream) -&gt; read_t&lt; T, std::reference_wrapper&lt; InputStreamT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>readbuf</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a6dac4023e221361610f4f65fee508057</anchor>
      <arglist>(InputStreamT &amp;stream) -&gt; readbuf_t&lt; std::reference_wrapper&lt; InputStreamT &gt;, std::array&lt; char, N &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>readbuf</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a9a8a0ac5d4f0bc817d5f1b4e11b11b30</anchor>
      <arglist>(InputStreamT &amp;stream, std::size_t n) -&gt; readbuf_t&lt; std::reference_wrapper&lt; InputStreamT &gt;, std::vector&lt; char &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>remove</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ad6801522a4749259f1da08257065abc3</anchor>
      <arglist>(PredicateT &amp;&amp;pred) -&gt; decltype(filter(complement(std::forward&lt; PredicateT &gt;(pred))))</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>repeat</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a93215c74409bd3b594605eaa624d4d18</anchor>
      <arglist>(ValueT &amp;&amp;r) -&gt; repeat_t&lt; estd::decay_t&lt; ValueT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>repeatn</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>abc8200b8f34aaaf847917234ce315d82</anchor>
      <arglist>(IntegralT &amp;&amp;n, ValueTs &amp;&amp;...rs) -&gt; decltype(comp(repeat(std::forward&lt; ValueTs &gt;(rs)...),                               take(std::forward&lt; IntegralT &gt;(n))))</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>replace</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>aa04b4d4796efe53d507356cb40d10ea0</anchor>
      <arglist>(TableT &amp;&amp;table) -&gt; decltype(map(detail::lookup_or_key&lt; estd::decay_t&lt; TableT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>replace_all</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>af34877a89c42bfdf11a53c7218f71302</anchor>
      <arglist>(TableT &amp;&amp;table) -&gt; decltype(map(detail::lookup_default&lt; estd::decay_t&lt; TableT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>replace_all_safe</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>aaad19ba27a1533eb710ce84f9c300915</anchor>
      <arglist>(TableT &amp;&amp;table) -&gt; decltype(map(detail::lookup_safe&lt; estd::decay_t&lt; TableT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>sink</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>af614a13bb66957508876cefc21cb4902</anchor>
      <arglist>(ActionT &amp;&amp;action) -&gt; sink_t&lt; estd::decay_t&lt; ActionT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>take</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>ad1392e213eac822dbbb8500608012bb4</anchor>
      <arglist>(IntegralT &amp;&amp;n) -&gt; take_t&lt; estd::decay_t&lt; IntegralT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>take_nth</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a17787884a59f85db0f31190809a9de80</anchor>
      <arglist>(IntegralT &amp;&amp;n) -&gt; take_nth_t&lt; estd::decay_t&lt; IntegralT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>take_while</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a68949f8b8b3369cd89c0f5e522b762c2</anchor>
      <arglist>(PredicateT &amp;&amp;p) -&gt; take_while_t&lt; estd::decay_t&lt; PredicateT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>traced</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a1c5626f067144894d8ba89075c02120a</anchor>
      <arglist>(std::string message) -&gt; decltype(map(tracer</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>write</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a59baa0dcd3ba01cca2f1eea15d284c8e</anchor>
      <arglist>(OutputStreamT &amp;stream, InSeparatorT in_sep=InSeparatorT{}) -&gt; write_t&lt; std::reference_wrapper&lt; OutputStreamT &gt;,                                               InSeparatorT,                                               InSeparatorT &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>writebuf</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a17cf9b4f857005aa681a5f59b78b9d11</anchor>
      <arglist>(OutputStreamT &amp;stream) -&gt; writebuf_t&lt; std::reference_wrapper&lt; OutputStreamT &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>with_state</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a688e55a0bcb50339f31752d3d49ba7d9</anchor>
      <arglist>(StateT &amp;&amp;st, UnwrappedFn &amp;&amp;, WrappedFn &amp;&amp;fn) -&gt; meta::lazy_enable_if_t&lt;              !std::is_same&lt;                      estd::decay_t&lt; StateT &gt;,                   estd::decay_t&lt; decltype(state_complete(st))&gt;           &gt;::value,           std::result_of&lt; WrappedFn(StateT)&gt;   &gt;</arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cat</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a7b3db0b1325b015399b0d50f75e33220</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr dedupe_t</type>
      <name>dedupe</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a4c6daf171c364c439a2595957a5d6b2d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr distinct_t</type>
      <name>distinct</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a71ceccfe79ea71598ee8534b2c7bade7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr sorted_t</type>
      <name>sorted</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a642cff3421f4c943d8f5039baa6feef9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr reversed_t</type>
      <name>reversed</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a9fc45ce6e33283e92568eee03414b0e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const enumerate_t&lt; std::size_t &gt;</type>
      <name>enumerate</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a674e6c72a9862bb0968da41dfbcbedef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>interleave</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a862d2b68690c1c4f277f48d9b677d5de</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>unzip</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>abe5308d966fbf95d317511a706d6d20a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const map_t&lt; tuplify_t &gt;</type>
      <name>zip</name>
      <anchorfile>namespaceatria_1_1xform.html</anchorfile>
      <anchor>a3002569b1ecc9b8b0e17d0de591c2915</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>testing</name>
    <title>Testing</title>
    <filename>testing</filename>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title></title>
    <filename>index</filename>
  </compound>
</tagfile>
