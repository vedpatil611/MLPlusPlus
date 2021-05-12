#pragma once

#include <imgui.h>
#include <imnodes/imnodes.h>
#include <NodeEditor/Object.h>

namespace Nodes
{
	class Node 
	{
	public:
		int start_id;
		Node(int id) : start_id(id) {}
		virtual void show() = 0;
		virtual int lastIdOffset() const = 0;
	};

	class Main: public Node
	{
	public:
		Main(int id);
		void show() override;
		inline int lastIdOffset() const override { return 2; }
		static inline constexpr int getIdIncreament() { return 2; }
	};

	class LinearRegression : public Node
	{
	public:
		LinearRegression(int id);
		void show() override;
		inline int lastIdOffset() const override { return 4; }
		static inline constexpr int getIdIncreament() { return 4; }
	};

	class LR_SetIterations : public Node
	{
	private:
		static inline int s_count = 0;
		int count;
		char value[8] = "";
	public:
		LR_SetIterations(int id);
		void show() override;
		inline int lastIdOffset() const override { return 5; }
		static inline constexpr int getIdIncreament() { return 5; }
	};

	class Set : public Node
	{
	private:
		static inline int s_count = 0;
		int count;
		char name[64] = "";
		Object* object;
	public:
		Set(int id, Object* obj = nullptr);
		void show() override;
		inline int lastIdOffset() const override { return 5; }
		static inline constexpr int getIdIncreament() { return 5; }
	};
	
	class Get : public Node
	{
	private:
		Object* object;
	public:
		Get(int id, Object* obj);
		void show() override;
		inline int lastIdOffset() const override { return 2; }
		static inline constexpr int getIdIncreament() { return 2; }
	};

	class FileReader : public Node
	{
	public:
		FileReader(int id);
		void show() override;
		inline int lastIdOffset() const override { return 4; }
		static inline constexpr int getIdIncreament() { return 4; }
	};
}