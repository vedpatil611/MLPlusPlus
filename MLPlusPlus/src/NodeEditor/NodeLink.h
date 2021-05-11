#pragma once

namespace Nodes
{
	class Link
	{
	public:
		int id;
		int start_id, end_id;

		Link(int id, int start, int end) : id(id), start_id(start), end_id(end) {}
	};
}