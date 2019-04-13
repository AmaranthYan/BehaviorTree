#pragma once

#include "Composite.h"

namespace BTree
{
	class Sequence : public Composite
	{
	protected:
		void Enter() override;
		EState Run() override;
	};
}