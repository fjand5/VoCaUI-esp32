<template>
  <el-container>
    <el-header
    height="60px"
    >
      <el-row
      type="flex"
      justify="space-between"
      align="center"
      >
        <el-col>
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
                  index="1-1">RESET</el-menu-item>
              
                  <el-menu-item 
                  index="1-1">
                  <el-upload
                    action="/update"
                    :auto-upload="true">
                    <el-button slot="trigger" size="small" type="primary">select file</el-button>
                  </el-upload>
                  </el-menu-item>
                  </el-submenu>
          </el-menu>
        </el-col>
        <el-col>
          <el-button 
          size="small"
          v-if="getCurrentWifi"
          class="wifi-button"
          @click="$showWifiSelector"
          > {{getCurrentWifi.ip}} </el-button>
          <el-button 
          v-else
          class="wifi-button"
          icon="el-icon-share" circle
          @click="$showWifiSelector"
          ></el-button>
          
        </el-col>
      </el-row>

    </el-header>
    <el-main>   
      <Panel/>           
    </el-main>
    <el-footer>Footer</el-footer>
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
      ...mapGetters(['getCurrentWifi'])
    },
    mounted:function(){
      this.$store.dispatch('updateCurrentWifi')
      this.$store.dispatch('initCommand')

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
  float: right;

  transform: translateY(45%);
}
.cell{
  cursor: pointer;
}
</style>