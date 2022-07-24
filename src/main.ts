import { createApp } from "vue";
import App from "./App.vue";
import router from "./router";
import store from "./store";

import "bootstrap/dist/js/bootstrap";
import "bootstrap/dist/css/bootstrap.css";
import "bootstrap-icons/font/bootstrap-icons.css";

import "simplebar";
import "simplebar/dist/simplebar.css";

import "./assets/mayuzumi-z.css";

createApp(App).use(store).use(router).mount("#app");
