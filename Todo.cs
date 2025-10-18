using System;
using System.Collections.Generic;
using System.IO;
using System.Text.Json;

class Todo
{
    public string Task { get; set; }
    public bool Done { get; set; }
}

class TodoApp
{
    static string path = "todos.json";

    static void Main()
    {
        List<Todo> todos = LoadTodos();

        Console.WriteLine("1. Add Task\n2. Show Tasks\n3. Exit");
        int choice = Convert.ToInt32(Console.ReadLine());

        if (choice == 1)
        {
            Console.Write("Enter task: ");
            todos.Add(new Todo { Task = Console.ReadLine(), Done = false });
            SaveTodos(todos);
        }
        else if (choice == 2)
        {
            foreach (var t in todos)
                Console.WriteLine($"{(t.Done ? "[x]" : "[ ]")} {t.Task}");
        }
    }

    static List<Todo> LoadTodos()
    {
        if (!File.Exists(path)) return new List<Todo>();
        string json = File.ReadAllText(path);
        return JsonSerializer.Deserialize<List<Todo>>(json);
    }

    static void SaveTodos(List<Todo> todos)
    {
        string json = JsonSerializer.Serialize(todos, new JsonSerializerOptions { WriteIndented = true });
        File.WriteAllText(path, json);
    }
}
