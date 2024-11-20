import React, {useEffect, useState} from 'react'
import { deleteSeason, listSeasons } from '../services/SeasonService'
import {useNavigate} from 'react-router-dom'


const ListSeasonComponent = () => {

    const [seasons, setSeasons] = useState([])

    const navigator = useNavigate();

    useEffect(() => {
        getAllSeasons();
    }, [])

    function getAllSeasons(){
        listSeasons().then((response) =>{
            setSeasons(response.data);
        }).catch(error => {
            console.error(error);
        })
    }

    function addNewSeason(){
        navigator('/add-season')
    }

    function updateSeason(id){
        navigator(`/edit-season/${id}`)
    }

    function removeSeason(id){
        console.log(id);
        deleteSeason(id).then((response)=>{
            getAllSeasons();
        }).catch(error=>{
            console.error(error);
        })
    }

  return (
    <div className='container'>

        <h2 className='text-center'>List of Seasons</h2>
        <button className='btn btn-primary' onClick={addNewSeason}>Add Season</button>
        <table className='table table-striped table-bordered'>
            <thead>
                <tr>
                    <th>Id</th>
                    <th>Name</th>
                    <th>Description</th>
                    <th>Number of Days</th>
                    <th>Actions</th>
                </tr>
            </thead>
            <tbody>
                {
                    seasons.map(season =>
                        <tr key={season.id}>
                            <td>{season.id}</td>
                            <td>{season.name}</td>
                            <td>{season.description}</td>
                            <td>{season.nrDays}</td>
                            <td>
                                <button className='btn btn-info' onClick={()=>updateSeason(season.id)}>Update</button>
                                <button className='btn bth-danger' onClick={() => removeSeason(season.id)}>Delete</button>
                            </td>
                        </tr>)
                }
            </tbody>
        </table>
    </div>
  )
}

export default ListSeasonComponent