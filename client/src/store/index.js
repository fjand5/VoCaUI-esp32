import Vue from 'vue'
import Vuex from 'vuex'
import wifi from './modules/wifi'
import mqtt from './modules/mqtt'
import system from './modules/system'
import command from './modules/command'
import render from './modules/render'


Vue.use(Vuex)

const store = new Vuex.Store({
    modules: [
        wifi,
        mqtt,
        system,
        command,
        render
    ]
})
export default store