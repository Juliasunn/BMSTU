import React from "react";
import TrakListItem from "./TrakListItem";
import '../index.css'
import { ITrak } from "../types";


interface TrakListProps {
    data: Array<ITrak>;
}

const TrakList: React.FC<TrakListProps> = ({data}) => {

    return (<div className="flex flex-col items-center justify-top-center overflow-y-scroll h-3/4 scrollbar-hide w-1/2 lg:py-0">
    {data.map((el: ITrak, key:number) => (<TrakListItem trakItem={el} key={key}></TrakListItem>))}
    </div>)
}


export default TrakList;