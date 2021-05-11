#pragma once

#include <imgui.h>
#include <imnodes/imnodes.h>

namespace Nodes
{
	class Node 
	{
	protected:
		int start_id;
		Node(int id) : start_id(id) {}
	public:
		virtual void show() = 0;
	};

	class Main: public Node
	{
	public:
		Main(int id);
		void show() override;
		static inline constexpr int getIdIncreament() { return 2; }
	};

	class LinearRegression : public Node
	{
	public:
		LinearRegression(int id);
		void show() override;
		static inline constexpr int getIdIncreament() { return 4; }
	};

	class LR_SetLearningRate : public Node
	{
	public:
		LR_SetLearningRate(int id);
		void show() override;
		static inline constexpr int getIdIncreament() { return 5; }
	};
}