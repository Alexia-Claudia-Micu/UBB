﻿namespace Template_Log.Models.Entities
{
    public class User
    {
        public int Id { get; set; }
        public string Username { get; set; }
        public string Password { get; set; } // Ideally, store hashed passwords
        public string Email { get; set; }
    }
}
