#pragma once
#include <AutoYams\core\exception\AbstractException.h>

#define __DECLARE_EXCEPTION(x, s) class x : public AbstractException  \
	{ public: explicit x(QString content = "") : AbstractException(content) { } \
	protected: QString entitled() const override { return s; } }


__DECLARE_EXCEPTION(GameException, "Game Error");
__DECLARE_EXCEPTION(DiceDetectionException, "Dice Detection Error");
__DECLARE_EXCEPTION(ConfigException, "Configuration Error");
__DECLARE_EXCEPTION(FileException, "File Error");

__DECLARE_EXCEPTION(BoundaryException, "Out of Bounds");
__DECLARE_EXCEPTION(UnallocatedException, "Undefined Pointer");