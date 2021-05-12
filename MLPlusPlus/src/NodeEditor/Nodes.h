#pragma once

#include <imgui.h>
#include <imfilebrowser.h>
#include <imnodes/imnodes.h>
#include <NodeEditor/Object.h>

namespace Nodes
{
	class Node 
	{
	public:
		int start_id;
		int p = -1, n = -1;
		Node* prev = nullptr;
		Node* next = nullptr;

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

	class LR_Train :public Node
	{
	private:
		static inline int s_count = 0;
		int count = 0;
		char rate[8] = "0.01";
		char iter[8] = "1000";
	public:
		LR_Train(int id);
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
	private:
		static inline int s_count = 0;
		int count = 0;
		char filename[64] = "";
		char filepath[256] = "";
		bool fileSelection = false;
		ImGui::FileBrowser fileDialog;
	public:
		FileReader(int id);
		void show() override;
		inline int lastIdOffset() const override { return 6; }
		static inline constexpr int getIdIncreament() { return 6; }
	};

	class FR_ReadColumn :public Node
	{
	private:
		static inline int s_count = 0;
		int count = 0;
		char columnName[32] = "";
	public:
		FR_ReadColumn(int id);
		void show() override;
		inline int lastIdOffset() const override { return 6; }
		static inline constexpr int getIdIncreament() { return 6; }
	};
}