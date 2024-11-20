import axios from "axios";

const REST_API_BASE_URL = 'http://localhost:8080/api/seasons';

export const listSeasons = () => axios.get(REST_API_BASE_URL);

export const createSeason = (season) => axios.post(REST_API_BASE_URL, season);

export const getSeason = (seasonId) => axios.get(REST_API_BASE_URL + '/' + seasonId);

export const updateSeason = (seasonId, season) => axios.put(REST_API_BASE_URL + '/' + seasonId, season);

export const deleteSeason = (seasonId) => axios.delete(REST_API_BASE_URL + '/' + seasonId);