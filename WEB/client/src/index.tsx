import ReactDOM from "react-dom/client";
import './index.css'
import App from "./App";

import { Provider } from 'react-redux'
import {store} from "./api/store";

const root = ReactDOM.createRoot(document.getElementById("root") as HTMLElement);

root.render(<Provider store={store}>
    <App ></App>
    </Provider>)
