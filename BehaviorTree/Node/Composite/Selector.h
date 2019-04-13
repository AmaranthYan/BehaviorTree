#pragma once

#include "Composite.h"

namespace BTree
{
	class Selector : public Composite
	{
	protected:
		void Enter() override;
		EState Run() override;
	};
}