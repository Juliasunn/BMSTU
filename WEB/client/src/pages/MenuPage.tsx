import { useState, useEffect } from "react";
import { useEditUserinfoMutation, useGetUserinfoQuery } from "../api/Api";
import { useAppSelector } from "../api/store";
import '../index.css'
import {FaUserCircle} from 'react-icons/fa'
import LogoComponent from "../components/basic";
import { ToastContainer} from 'react-toastify';
import {createErrorMessage, createSuccessMessage} from '../components/Messages'
import { MinRegDataLen, SearchPath, FavPath } from "../constants";
import {StandartButton, NavigateButton } from "../components/basic"


const inputClassName = "bg-gray-50 border border-gray-300 text-gray-900 sm:text-sm rounded-lg focus:ring-primary-600 focus:border-primary-600 block w-full p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500"


const MenuPage: React.FC<{}> = () => {

    useGetUserinfoQuery(localStorage.getItem("access_token"));
    const currentUserinfo = useAppSelector((state) => state.userinfoState)

    const [newPassord, setNewPassword] = useState("");
    const [setUser, resEditUser] = useEditUserinfoMutation();

    useEffect(() => { //обработка ответа от сервера
        if (resEditUser.isSuccess){
          createSuccessMessage("Пароль изменен!");   
        }
        else if (resEditUser.isError) {
          createErrorMessage("Ошибка: не удалось изменить пароль!");
        }
    })

    function changePasswordHandler () {
        if (newPassord.length < MinRegDataLen ) {
            createErrorMessage("Пароль должен содержать не менее" + MinRegDataLen + "символов!");
            return;
        }
        setUser({NewPassword:newPassord}); 
    }
    return <div className="flex flex-col items-center justify-center px-6 py-8 mx-auto md:h-screen w-screen lg:py-0">
         <LogoComponent></LogoComponent>
        <h1 className="text-2xl font-bold text-cyan-500 shadow-xl">Аккаунт</h1>

        <FaUserCircle className="w-1/4 h-1/4 m-1 text-black/50"></FaUserCircle>
        <h1 className="text-xl font-semibold text-cyan-500 ">Имя пользователя: {currentUserinfo.login}</h1>

        <h1 className="text-xl font-semibold text-cyan-500">Изменить пароль:</h1>

        <div className="flex flex-row items-center justify-center">

        <input className={inputClassName} type="text" placeholder="Введите новый пароль" value={newPassord}
        onChange={(event: React.ChangeEvent<HTMLInputElement>) => setNewPassword(event.target.value)}
        ></input>

       <StandartButton func={changePasswordHandler} text="Изменить"></StandartButton>
        </div>
        <NavigateButton path={SearchPath} text="Поиск"></NavigateButton>
        <NavigateButton path={FavPath} text="Избранное"></NavigateButton>
        <ToastContainer />
    </div>
}

export default MenuPage;