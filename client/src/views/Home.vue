<template>
  <el-container>
    <el-header
    height="60px"
    >
      <el-row type="flex" justify="start">
        <el-col :span="12">
          <el-menu
          class="el-menu-demo"
          mode="horizontal"
          background-color="#545c64"
          text-color="#fff"
          active-text-color="#ffd04b"
          menu-trigger="click"
          >
              <el-submenu index="1">
                  <template slot="title">Setting</template>
                  <!-- <el-menu-item 
                  @click="$showMqttSetting"
                  index="1-1">MQTT</el-menu-item> -->
                  <el-menu-item 
                  @click="$store.dispatch('reset')"
                  index="1-1">RESET {{getUptime}}</el-menu-item>
              
                  <el-menu-item 
                  index="1-1">
                  <el-upload
                    action="/update"
                    :auto-upload="true">
                    <el-button slot="trigger" size="small" type="primary">Upload</el-button>
                  </el-upload>
                  </el-menu-item>
                  </el-submenu>
          </el-menu>
        </el-col>
        <el-col  :span="12" class="wifi-button">
          <el-button 
          size="small"
          v-if="getCurrentWifi"
          class="wifi-button"
          @click="$showWifiSelector"
          > {{getCurrentWifi.ip}} 
          <el-tag :type="getResponseTime<2000?getResponseTime<1000?'success':'warning':'danger'" size="mini">{{getResponseTime}}ms</el-tag>
          </el-button>
          <el-button 
          v-else
          class="wifi-button"
          icon="el-icon-share" circle
          @click="$showWifiSelector"
          ></el-button>
        </el-col>
      </el-row>

    </el-header>
    <el-main
    
    v-loading="getSending"
    >   
      <Panel/>           
    </el-main>
    <el-footer>Email: huynhtheluat@gmail.com</el-footer>
  </el-container>
</template>

<script>
import {mapGetters} from 'vuex'
import Panel from './Panel.vue'
export default {
    data() {
      return {
        activeIndex: '1',
        activeIndex2: '1',


      };
    },
    components:{
      Panel
    },
    computed:{
      ...mapGetters(['getCurrentWifi','getSending', 'getResponseTime','getUptime'])
    },
    mounted:function(){
      this.$store.dispatch('updateCurrentWifi')

    },
    methods: {
    }

}
</script>

<style scoped>
.el-header{
  background: #545c64;
}
.wifi-button{
  display: flex;
  justify-content: end;
  align-items: center;
}
.cell{
  cursor: pointer;
}
</style>