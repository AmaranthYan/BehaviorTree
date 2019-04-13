#pragma once

#include "Decorator.h"

namespace BTree
{
	class UntilSuccess : public Decorator
	{
	protected:
		EState Run() override;
	};
}