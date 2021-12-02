import WifiSelector from './views/WifiSelector'
import MqttSetting from './views/MqttSetting'

import store from './store';
let ServicePlugin =
{ 
  
  install:function (Vue) {

    Vue.prototype.$showWifiSelector = function () {
      var ComponentClass = Vue.extend(WifiSelector)
      var instance = new ComponentClass({store: store})
      instance.$mount()
    }
    Vue.prototype.$showMqttSetting = function () {
      var ComponentClass = Vue.extend(MqttSetting)
      var instance = new ComponentClass({store: store})
      instance.$mount()
    }
    Vue.$sendCommand = function () {
      return this.$loading({
        lock: true,
        text: 'please wait...',
        spinner: 'el-icon-loading',
        background: 'rgba(0, 0, 0, 0.6)'
      });
    }
  }
} 
export default ServicePlugin