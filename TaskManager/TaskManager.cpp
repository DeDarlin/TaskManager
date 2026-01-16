#include <fstream>
#include "TaskManager.h"
#include "Menu.h"
#include "Console.h"
#include "utils.h"

void TaskManager::AddTask()
{
	Console::Clear();

	size_t id;

	try
	{
		id = utils::CountLines("Tasks.txt") + 1;
	}
	catch (const std::runtime_error& e)
	{
		id = 1;
	}
	catch (const size_t& n)
	{
		id = n;
	}

	ofstream out("Tasks.txt", ios::app);
	if (!out.is_open())
	{
		cout << "Error: failed to open file";
		return;
	}

	out << id << "|";

	string task_name, task_description, due_date;
	gotoxy(45, 12);
	cout << "Enter task name: "; getline(cin, task_name);
	out << task_name << "|";
	gotoxy(45, 13);
	cout << "Enter task description: "; getline(cin, task_description);
	out << task_description << "|";
	out << "-" << "|"; // "-" means not completed
	gotoxy(45, 14);
	cout << "Enter due date (DD-MM-YYYY): "; getline(cin, due_date);
	if (due_date.empty()) due_date = "-"; // "-" means no due date
	out << due_date << endl;
	out.close();

	Console::Clear();
	cout << "Task added successfully";
	Console::SleepMs(2000);
}

void TaskManager::ShowTasks()
{
	Console::Clear();
	ifstream in("Tasks.txt");
	if (!in.is_open())
	{
		cout << "Error: failed to open file";
		Console::SleepMs(2000);
		return;
	}
	
	if  (in.peek() == EOF)
	{
		cout << "No tasks found.";
		Console::SleepMs(2000);
		return;
	}

	string line;
	while (getline(in, line))
	{
		size_t pos = 0;
		string token;
		vector<string> tokens;
		while ((pos = line.find("|")) != string::npos)
		{
			token = line.substr(0, pos);
			tokens.push_back(token);
			line.erase(0, pos + 1);
		}
		tokens.push_back(line);

		cout << "ID: " << tokens[0] << endl << endl;
		cout << "Name: " << tokens[1] << endl;
		cout << "Description: " << tokens[2] << endl;
		cout << "Status: " << (tokens[3] == "-" ? "Not Completed" : "Completed") << endl;
		cout << "Due Date: " << tokens[4] << endl << endl; 
		cout << "------------------------" << endl << endl;
	}
	Console::SleepMs(2000);
}

void TaskManager::EditName()
{
	Console::Clear();

	int id;
	gotoxy(45, 12);
	cout << "Enter task ID to edit: "; cin >> id;
	cin.ignore();

	ifstream in("Tasks.txt");
	if (!in.is_open())
	{
		cout << "Error: failed to open file";
		Console::SleepMs(2000);
		return;
	}

	if (in.peek() == EOF)
	{
		cout << "No tasks found.";
		Console::SleepMs(2000);
		return;
	}

	string line;
	
	while (getline(in, line))
		if (int(line[0]) != id)
			break;

	line.erase(0, line.find("|") + 1);
	string NewName;
	gotoxy(45, 13);
	cout << "Enter new task name: "; getline(cin, NewName);
	size_t pos = line.find("|");
	line = to_string(id) + "|" + NewName + "|" + line.substr(pos + 1);
	in.close();

	utils::ChangeLine("Tasks.txt", id, line);
	Console::Clear();
	gotoxy(45, 12);
	cout << "Task name updated successfully";
	Console::SleepMs(2000);
}

void TaskManager::EditDescription()
{
	Console::Clear();

	int id;
	gotoxy(45, 12);
	cout << "Enter task ID to edit: "; cin >> id;
	cin.ignore();

	ifstream in("Tasks.txt");
	if (!in.is_open())
	{
		cout << "Error: failed to open file";
		Console::SleepMs(2000);
		return;
	}

	if (in.peek() == EOF)
	{
		cout << "No tasks found.";
		Console::SleepMs(2000);
		return;
	}

	string line;

	while (getline(in, line))
		if (int(line[0]) != id)
			break;

	line.erase(0, line.find("|") + 1);
	string name = line.substr(0, line.find("|"));
	line.erase(0, line.find("|") + 1);

	string NewDescription;

	gotoxy(45, 13);
	cout << "Enter new task description: "; getline(cin, NewDescription);
	size_t pos = line.find("|");
	line = to_string(id) + "|" + name + "|" + NewDescription + "|" + line.substr(pos + 1);
	in.close();

	utils::ChangeLine("Tasks.txt", id, line);
	Console::Clear();
	gotoxy(45, 12);
	cout << "Task name updated successfully";
	Console::SleepMs(2000);
}

void TaskManager::EditDueDate()
{
	Console::Clear();

	int id;
	gotoxy(45, 12);
	cout << "Enter task ID to edit: "; cin >> id;
	cin.ignore();

	ifstream in("Tasks.txt");
	if (!in.is_open())
	{
		cout << "Error: failed to open file";
		Console::SleepMs(2000);
		return;
	}

	if (in.peek() == EOF)
	{
		cout << "No tasks found.";
		Console::SleepMs(2000);
		return;
	}

	string line;

	while (getline(in, line))
		if (int(line[0]) != id)
			break;

	line.erase(0, line.find("|") + 1);
	string name = line.substr(0, line.find("|"));
	line.erase(0, line.find("|") + 1);
	string description = line.substr(0, line.find("|"));
	line.erase(0, line.find("|") + 1);
	string completed = line.substr(0, line.find("|"));
	line.erase(0, line.find("|") + 1);

	string NewDueDate;

	gotoxy(45, 13);
	cout << "Enter new due date: "; getline(cin, NewDueDate);
	size_t pos = line.find("|");
	line = to_string(id) + "|" + name + "|" + description + "|" + completed + "|" + NewDueDate + "|" + line.substr(pos + 1);
	in.close();

	utils::ChangeLine("Tasks.txt", id, line);
	Console::Clear();
	gotoxy(45, 12);
	cout << "Task name updated successfully";
	Console::SleepMs(2000);
}

void TaskManager::EditTask()
{
	bool flag = true;
	while (flag)
	{
		Console::Clear();
		int c = Menu::select_vertical({ "Edit name", "Edit description", "Edit due date", "Exit"}, Center, 12);
		switch (c)
		{
			case 0:
				EditName();
				break;
			case 1:
				EditDescription();
				break;
			case 2:
				EditDueDate();
				break;
			case 3:
				flag = false;
				break;
		}
	}
}

void TaskManager::RemoveTask()
{
	Console::Clear();
	int id;
	gotoxy(45, 12);
	cout << "Enter task ID to delete: "; cin >> id;
	cin.ignore();
	ifstream in("Tasks.txt");
	if (!in.is_open())
	{
		cout << "Error: failed to open file";
		Console::SleepMs(2000);
		return;
	}
	if (in.peek() == EOF)
	{
		cout << "No tasks found.";
		Console::SleepMs(2000);
		return;
	}
	in.close();
	utils::RemoveLine("Tasks.txt", id);
	Console::Clear();
	gotoxy(45, 12);
	cout << "Task deleted successfully";
	Console::SleepMs(2000);
}

void TaskManager::MarkTaskAsCompleted()
{
	Console::Clear();
	int id;
	gotoxy(45, 12);
	cout << "Enter task ID to mark as completed: "; cin >> id;
	cin.ignore();
	ifstream in("Tasks.txt");
	if (!in.is_open())
	{
		cout << "Error: failed to open file";
		Console::SleepMs(2000);
		return;
	}
	if (in.peek() == EOF)
	{
		cout << "No tasks found.";
		Console::SleepMs(2000);
		return;
	}
	string line;
	while (getline(in, line))
		if (int(line[0]) != id)
			break;
	line.erase(0, line.find("|") + 1);
	string name = line.substr(0, line.find("|"));
	line.erase(0, line.find("|") + 1);
	string description = line.substr(0, line.find("|"));
	line.erase(0, line.find("|") + 1);
	string due_date = line.substr(line.find_last_of("|") + 1);
	line = to_string(id) + "|" + name + "|" + description + "|Completed|" + due_date;
	in.close();
	utils::ChangeLine("Tasks.txt", id, line);
	Console::Clear();
	gotoxy(45, 12);
	cout << "Task marked as completed successfully";
	Console::SleepMs(2000);
}

void TaskManager::run()
{
	bool flag = true;
	while (flag)
	{
		Console::Clear();
		int c = Menu::select_vertical({ "Add Task", "Show Tasks", "Edit Tasks", "Delete Task", "Mark task as completed", "Exit" }, Center, 12);
		switch (c)
		{
		case 0:
			AddTask();
			break;
		case 1:
			ShowTasks();
			break;
		case 2:
			EditTask();
			break;
		case 3:
			RemoveTask();
			break;
		case 4:
			MarkTaskAsCompleted();
			break;
		case 5:
			flag = false;
			break;
		}
	}
}