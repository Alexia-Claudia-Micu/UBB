import React, { useEffect, useState } from 'react'
import { createSeason, updateSeason,  getSeason } from '../services/SeasonService';
import{useNavigate, useParams} from 'react-router-dom'

const SeasonComponent = () => {

  const [name, setName] = useState('');
  const [description, setDescription] = useState('');
  const [nrDays, setNrDays] = useState(-1);

  const {id} = useParams();

  const [errors, setErrors] = useState({
    name:'',
    description:'',
    nrDays:''
  })
  const navigator = useNavigate();

  useEffect(()=>{
    if(id){
      getSeason(id).then((response) =>{
        setName(response.data.name);
        setDescription(response.data.description);
        setNrDays(response.data.nrDays);
      }).catch(error =>{
        console.error(error);
      })
    }
  },[id])

  function saveOrUpdateSeason(e){
      e.preventDefault();

      if(validateForm()){

        const season = {name, description, nrDays}
        console.log(season)

        if(id){
          updateSeason(id, season).then((response) =>{
            console.log(response.data);
            navigator('/seasons');
          }).catch(error => {
            console.error(error);
          })
        }else{
          createSeason(season).then((response) =>{
            console.log(response.data);
            navigator('/seasons')
          }).catch(error => {
            console.error(error);
          })
        }
      }
  }

  function validateForm(){
    let valid = true;
    const errorsCopy = {... errors}

    if(name.trim()){
      errorsCopy.name ='';
    }else{
      errorsCopy.name = 'Name is required';
      valid = false;
    }

    if(description.trim()){
      errorsCopy.description='';
    }else{
      errorsCopy.description ='Description is required';
      valid = false;
    }

    if(nrDays.trim()){
      errorsCopy.nrDays='';
    }else{
      errorsCopy.nrDays ='Days required';
      valid = false;
    }

    setErrors(errorsCopy);
    return valid;
  }

  function pageTitle(){
      if(id){
        return <h2 className='text-center'>Update Season</h2>
      } else{
        return <h2 className='text-center'>Add Season</h2>
      }
  }

  return (
    <div className='container'>
      <br></br>
      <div className='row'>
        <div className='card col-md-6 offset-md-3 offset-md-3'>
          {
            pageTitle()
          }
            <div className='card-body'>
              <form>
                <div className='form-group mb-2'>
                  <label className='form-label'>Name:</label>
                  <input
                    type='text'
                    placeholder='Enter Season Name'
                    name='name'
                    value={name}
                    className = {`form-control ${ errors.name ? 'is-invalid': ''}`}
                    onChange={(e) => setName(e.target.value)}
                  >
                  </input>
                  {errors.name && <div className='invalid-feedback'>{errors.name}</div>}
                </div>

                <div className='form-group mb-2'>
                  <label className='form-label'>Description:</label>
                  <input
                    type='text'
                    placeholder='Enter Season Desription'
                    name='description'
                    value={description}
                    className = {`form-control ${ errors.description ? 'is-invalid': ''}`}
                    onChange={(e) => setDescription(e.target.value)}
                  >
                  </input>
                  {errors.description && <div className='invalid-feedback'>{errors.description}</div>}

                </div>

                <div className='form-group mb-2'>
                  <label className='form-label'>Number of Days:</label>
                  <input
                    type='number'
                    placeholder='Days'
                    name='nrDays'
                    value={nrDays}
                    className = {`form-control ${ errors.nrDays ? 'is-invalid': ''}`}
                    onChange={(e) => setNrDays(e.target.value)}
                  >
                  </input>
                  {errors.nrDays && <div className='invalid-feedback'>{errors.nrDays}</div>}

                </div>
                <button className='btn btn-success' onClick={saveOrUpdateSeason}>Submit</button>
              </form>
            </div>
        </div>
      </div>
    </div>
  )
}

export default SeasonComponent