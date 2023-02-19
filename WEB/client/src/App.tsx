import React from "react";
import { BrowserRouter } from "react-router-dom";
import NavigationRoutes from "./NavigationRoutes";
import './index.css'

const App: React.FC<{}> = () => {

        return <div className="App">
            <BrowserRouter>
            <NavigationRoutes></NavigationRoutes>
            </BrowserRouter>          
            </div>
}

export default App