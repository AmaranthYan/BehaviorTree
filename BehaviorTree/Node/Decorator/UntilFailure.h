#pragma once

#include "Decorator.h"

namespace BTree
{
	class UntilFailure : public Decorator
	{
	protected:
		EState Run() override;
	};
}