import { useState } from 'react'
import './App.css'
import ListSeasonComponent from './components/ListSeasonComponent'
import {BrowserRouter, Routes, Route} from 'react-router-dom'
import SeasonComponent from './components/SeasonComponent'


function App() {
  return (
    <>
    <BrowserRouter>
      <Routes>
        <Route path='/' element = {<ListSeasonComponent />}></Route>
        <Route path='/seasons' element = {<ListSeasonComponent />}></Route>
        <Route path='/add-season' element = {<SeasonComponent />} ></Route>
        <Route path='/edit-season/:id' element = {<SeasonComponent />} ></Route>

      </Routes>
    </BrowserRouter>
    </>
  )
}

export default App
