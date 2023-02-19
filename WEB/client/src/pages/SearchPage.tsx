import React from 'react'
import '../index.css'
import { useGetTraksQuery } from '../api/Api';
import TrakList from '../components/TrakList';
import { useAppSelector, useAppDispatch} from '../api/store';
import {ImSearch} from 'react-icons/im'
import PlayerItem from '../components/PlayerItem';
import { setPlaylist } from '../slices/playerSlice';
import {useState} from 'react'
import { ITrak } from '../types';
import { ToastContainer} from 'react-toastify';
import {SelectWithLabel} from '../components/SelectItem' 
import {Genres,  Sorts} from '../constants'
import { searchFunc, filterFunc, compareDate, compareListenings } from '../functions';
import { MenuNavigate } from "../components/basic"



const searchInputClassName = "w-100 bg-black/50 border border-gray-300 text-gray-300 sm:text-sm rounded-lg focus:ring-primary-600 focus:border-primary-600 block  p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500"

const SearchPage: React.FC<({})> = () => {

  const {requestId, error} = useGetTraksQuery(localStorage.getItem("access_token"));
  const [searchValue, setSearchValue] = useState("");
  const [filterValue, setFilterValue] = useState(Genres[0]);
  const [sortValue, setSortValue] = useState(Sorts[0]);

  let currentTraks = (useAppSelector( (state) => state.traklistState)).filter((trak) => (
  searchFunc (trak, searchValue) && filterFunc(trak, filterValue)) ).sort(compareFunc);

  const dispatch = useAppDispatch();
  dispatch(setPlaylist(currentTraks));

  function compareFunc(trak1:ITrak, trak2:ITrak) : number {
    if (sortValue === Sorts[1]) {
      return compareDate(trak1, trak2);   
    }
  return compareListenings(trak1, trak2);
  }

  return (
    <div > <MenuNavigate></MenuNavigate>
    <div className="flex flex-col items-center justify-center mx-auto md:h-screen md:w-screen lg:py-0">

      <h1 className="m-3 text-4xl font-bold text-cyan-500 shadow-xl">Глобальный поиск</h1>

      <div className="flex flex-row w-fill">
      <ImSearch className="ImSearch"> </ImSearch>

      <input className={searchInputClassName} type="text" placeholder="Введите название трека"
      value={searchValue} onChange = {(event: React.ChangeEvent<HTMLInputElement>) => (setSearchValue(event.target.value))}
      ></input>   
      </div>

      <div className="flex flex-row items-center justify-center">

      <SelectWithLabel labelText='Жанры' options={Genres} func={setFilterValue}></SelectWithLabel>

      <SelectWithLabel labelText='Порядок отображения' options={Sorts} func={setSortValue}></SelectWithLabel>
      </div>
      <ToastContainer />

      <TrakList data={currentTraks}></TrakList>
      <PlayerItem ></PlayerItem>
    </div>
    </div>
  )

} 



export default SearchPage;