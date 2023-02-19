import {ImMusic} from "react-icons/im"
import '../index.css'
import { Link } from "react-router-dom"

import {RiMenuFoldFill} from 'react-icons/ri'
import { MenuPath } from "../constants"
import { useNavigate } from "react-router-dom";

const LogoComponent: React.FC<{}> = () => {
return (
    <h1 className="mt-20 flex flex-row items-center justify-center drop-shadow-lg text-4xl font-bold text-cyan-500" >
        <ImMusic className="m-3"></ImMusic> LikeMusic </h1>
)

}

export const MenuNavigate: React.FC<{}> = () => {
    const navigate = useNavigate();
    return (
        <RiMenuFoldFill  onClick={() => (navigate(MenuPath))} className="RiMenuFoldFill">
        </RiMenuFoldFill>
    )   
}



export interface StandartButtonProps {
    func: () => void,
    text: string
};

const btnClassName="object-center w-full text-white bg-primary-600 hover:bg-primary-700  font-medium rounded-lg text-lg px-5 py-2.5 text-center hover:bg-white/25"

const btnContainerClassName="m-5 object-fill w-3/5 flex flex-col items-center justify-center  rounded-lg bg-cyan-500 shadow-lg shadow-cyan-500/50 "

export const StandartButton: React.FC<StandartButtonProps> = ({func, text}) => {
    return (
   <div className={btnContainerClassName}>
  <button type="button" className={btnClassName} onClick={func}> {text}  
  </button> 
  </div>
  )   
}

export interface NavigateButtonProps {
    path: string,
    text: string
};

const linkContainerClassName="m-5 object-fill w-1/4 flex flex-col items-center justify-center  rounded-lg bg-cyan-500 shadow-lg shadow-cyan-500/50 hover:bg-primary-200"

export const NavigateButton: React.FC<NavigateButtonProps> = ({path, text}) => {
    return (
        <div className={linkContainerClassName}>
        <Link className={btnClassName}  to={path}>{text}</Link>
        </div>
  )
    
}



export default LogoComponent