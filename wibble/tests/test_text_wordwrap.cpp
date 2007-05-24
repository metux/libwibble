#include <wibble/config.h>
#include <wibble/text/wordwrap.h>
#include <wibble/tests/tut-wibble.h>

namespace tut {

struct wibble_text_wrap_shar {
};
TESTGRP(wibble_text_wrap);

using namespace wibble::text;

template<> template<>
void to::test<1>()
{
	WordWrap ww("The quick brown  fox  jumps over the lazy dog");
	ensure_equals(ww.get(5), string("The"));
	ensure_equals(ww.get(14), string("quick brown"));
	ensure_equals(ww.get(3), string("fox"));

	// A line always gets some text, to avoid looping indefinitely in case of
	// words that are too long.  Words that are too long are split crudely.
	ensure_equals(ww.get(2), string("ju"));
	ensure_equals(ww.get(10), string("mps over"));
	ensure_equals(ww.get(3), string("the"));
	ensure_equals(ww.get(90), string("lazy dog"));
}

}

// vim:set ts=4 sw=4:
