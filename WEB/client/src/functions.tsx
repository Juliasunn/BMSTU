import {ITrak } from './types'
import { Genres, Sorts } from './constants';


export function searchFunc (trak:ITrak, searchValue:string): boolean {
    return ((trak.name).indexOf(searchValue) === 0 );
  }

  export function filterFunc (trak:ITrak, filterValue:string): boolean {
    if (filterValue === Genres[0]) {
      return true;
    }
    return (trak.genre === filterValue ) ;
  }


  export function compareDate(trak1:ITrak, trak2:ITrak) : number {
    let ret = 0;
    if (trak1.guid > trak2.guid) {
        return 1;
    }     
    if (trak1.guid < trak2.guid) {
        return -1;
    }
    return ret;
  }

  export function compareListenings(trak1:ITrak, trak2:ITrak) : number {
    let ret = 0;
    return ret;
  }