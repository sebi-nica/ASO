using Microsoft.AspNetCore.Mvc;
using TodoMvc.Data;
using TodoMvc.Models;

namespace TodoMvc.Controllers;

public class HomeController : Controller
{
    private readonly AppDbContext _db;

    public HomeController(AppDbContext db)
    {
        _db = db;
    }

    public IActionResult Index()
    {
        var todos = _db.Todos.ToList();
        return View(todos);
    }

    [HttpPost]
    public IActionResult Add(string name)
    {
        if (!string.IsNullOrEmpty(name))
        {
            _db.Todos.Add(new Todo { Name = name, IsComplete = false });
            _db.SaveChanges();
        }
        return RedirectToAction("Index");
    }

    [HttpPost]
    public IActionResult Delete(int id)
    {
        var todo = _db.Todos.Find(id);
        if (todo != null)
        {
            _db.Todos.Remove(todo);
            _db.SaveChanges();
        }
        return RedirectToAction("Index");
    }
}