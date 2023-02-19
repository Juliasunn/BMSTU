import {toast } from 'react-toastify';
import 'react-toastify/dist/ReactToastify.css';


export const createSuccessMessage = (msg:string) =>  {
    toast.success(msg, {
        position: "top-center",
    });  
}

export const createErrorMessage  = (msg:string) => {
    toast.error(msg, {
        position: "top-center",
      })  
}


