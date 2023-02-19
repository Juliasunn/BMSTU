import React, { useState, useEffect } from "react";
import { ToastContainer} from 'react-toastify';
import '../index.css'
import {useLoginUserMutation, useRegisterUserMutation } from "../api/Api";
import { useNavigate } from "react-router-dom";
import  LogoComponent from "../components/basic"
import {createErrorMessage, createSuccessMessage} from '../components/Messages'
import { MinRegDataLen, MenuPath } from "../constants";
import {StandartButton} from "../components/basic"


const inputClassName = "m-5 w-4/5 bg-gray-50 border border-gray-300 text-gray-900 sm:text-sm rounded-lg focus:ring-primary-600 focus:border-primary-600 block w-full p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500"


const AuthPage: React.FC<{}> = () => {
  
  const navigate = useNavigate();
  const [loginUser, resultLogin] = useLoginUserMutation();
  const [registerUser, resultRegister] = useRegisterUserMutation();

  useEffect(() => { //обработка ответа от сервера
    if (resultLogin.isSuccess) {
      createSuccessMessage("Вы успешно авторизовались!");
      navigate(MenuPath);
    }
    else if (resultLogin.isError) {
      createErrorMessage("Ошибка: неверный логин или пароль!");
      
    }
    if (resultRegister.isSuccess){
      createSuccessMessage("Вы успешно зарегистрировались!");
      navigate(MenuPath);

    }
    else if (resultRegister.isError) {
      createErrorMessage("Ошибка: пользователь уже существует!");
    }
    })

  const [login, setLogin] = useState("Juliasunn");
  const [password, setPassword] = useState("password123");

  const loginActionHandler = () => {
    localStorage.removeItem("access_token");
    loginUser({login:login, password:password});
  }
  
  const registerActionHandler = () => {
    if ((password.length < MinRegDataLen ) || (login.length < MinRegDataLen )) {
          createErrorMessage("Логин и пароль должны содержать не менее"+ MinRegDataLen +"символов!");
      return;
  }
    localStorage.removeItem("access_token");
    registerUser({login:login, password:password});
  }


  return ( <div className="flex flex-col items-center justify-center px-6 py-8 mx-auto md:h-screen lg:py-0">

  <h1 className="m-5 text-4xl font-bold text-cyan-500">
  Добро пожаловать в  <LogoComponent></LogoComponent>
  </h1>

  <h1 className="text-lg font-bold text-cyan-500 shadow-xl">Авторизуйтесь или создайте аккаунт</h1>

  <input className={inputClassName}type="text" placeholder="Введите логин" value={login}
  onChange={(event: React.ChangeEvent<HTMLInputElement>) => setLogin(event.target.value)}></input>
                    
  <input type = "text" placeholder="Введите пароль" value={password} className={inputClassName}
  onChange={(event: React.ChangeEvent<HTMLInputElement>) => setPassword(event.target.value)}></input>
                     
  <StandartButton func = {loginActionHandler} text={"Войти"}></StandartButton>
  <StandartButton func = {registerActionHandler} text={"Зарегистрироваться "}></StandartButton>

  <ToastContainer />                    
  </div>)
}

export default AuthPage