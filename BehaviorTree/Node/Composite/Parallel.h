#pragma once

#include "Composite.h"

namespace BTree
{
	class Parallel : public Composite
	{
	public:
		Parallel(bool stop_on_fail) : stop_on_fail(stop_on_fail) {}

	protected:
		EState Run() override;

	private:
		bool stop_on_fail;
	};
}