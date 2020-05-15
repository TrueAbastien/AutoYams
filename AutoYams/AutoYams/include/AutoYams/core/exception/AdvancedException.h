#pragma once
#include <AutoYams\core\exception\AbstractException.h>

/**
* Dev notes, exception handling:
* While those where used to handle specific cases scenarios in a (unpublished) most recent
* program version, they were quickly removed after being linked to major issues keeping the
* application from even running/starting as expected.
* Exceptions have proven themselves to be dangerously problematics in their current use
* which is why, despite the effort made to implement them, they will not be present
* in the final product (as of now). An heap memory corruption seems to be partially
* responsible for the problems that led me to believe of the current problematic that
* exceptions COULD have caused, perhaps it would better to look for possible memory leaks
* in the future. I don't have time nor courage for this though.
*/

#define __DECLARE_EXCEPTION(x, s) class x : public AbstractException  \
	{ public: explicit x(QString content = "") : AbstractException(content) { } \
	protected: QString entitled() const override { return s; } }


__DECLARE_EXCEPTION(GameException, "Game Error");
__DECLARE_EXCEPTION(DiceDetectionException, "Dice Detection Error");
__DECLARE_EXCEPTION(ConfigException, "Configuration Error");
__DECLARE_EXCEPTION(FileException, "File Error");
__DECLARE_EXCEPTION(JSONException, "JSON Error");

__DECLARE_EXCEPTION(BoundaryException, "Out of Bounds");
__DECLARE_EXCEPTION(UnallocatedException, "Undefined Pointer");
__DECLARE_EXCEPTION(UnfitContent, "Content isn't fit");