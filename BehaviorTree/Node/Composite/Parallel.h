#pragma once

#include "Composite.h"

namespace BTree
{
	class Parallel : public Composite
	{
	public:
		Parallel(bool abort_on_fail) : abort_on_fail(abort_on_fail) {}

	protected:
		EState Run() override;

	private:
		bool abort_on_fail;
	};
}