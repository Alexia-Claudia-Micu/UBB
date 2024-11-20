import { useState } from "react";
import reactLogo from "./assets/react.svg";
import viteLogo from "/vite.svg";
import "./App.css";
import { BrowserRouter as Router, Route, Routes } from "react-router-dom";
import Home from "./components/Home.js";
import Seasons from "./components/Seasons.js";
import Button from "react-bootstrap";
import Add from "./components/Add.js";
import Edit from "./components/Edit";
import Details from "./components/Details.js";

function App() {
  return (
    <div className="App">
      <Router>
        <Routes>
          <Route path="/" element={<Home />} />
          <Route path="/create" element={<Add />} />
          <Route path="/edit" element={<Edit />} />
          <Route path="/details/:name" element={<Details />} />
        </Routes>
      </Router>
    </div>
  );
}

export default App;
