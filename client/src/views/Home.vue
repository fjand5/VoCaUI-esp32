<template>
  <el-container>
    <el-header height="60px">
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
              <template slot="title">Menu</template>
              <el-menu-item
                v-if="getManifest.mqtt"
                @click="$showMqttSetting"
                index="1-1"
                >MQTT</el-menu-item
              >
              <el-menu-item @click="$store.dispatch('reset')" index="1-1"
                >RESET {{ getUptime }}</el-menu-item
              >
              <el-menu-item
                v-if="getManifest.auth"
                @click="$showChangePassword"
                index="1-1"
                >Đổi mật khẩu</el-menu-item
              >
              <el-menu-item
                v-if="getManifest.auth"
                @click="$showLogin"
                index="1-1"
                >Đăng nhập</el-menu-item
              >
              <el-menu-item
                v-if="getManifest.auth"
                @click="
                  $store.dispatch('logout');
                  $store.dispatch('closeWebsocket');
                "
                index="1-1"
                >Đăng xuất</el-menu-item
              >

              <el-menu-item v-if="getManifest.upload" index="1-1">
                <el-upload action="/update" :auto-upload="true">
                  <el-button slot="trigger" size="small" type="primary"
                    >Upload</el-button
                  >
                </el-upload>
              </el-menu-item>
            </el-submenu>
          </el-menu>
        </el-col>
        <el-col :span="12" class="wifi-button">
          <el-button
            size="small"
            v-if="getAuthStatus && getCurrentWifi"
            class="wifi-button"
            @click="showWifi"
          >
            {{ getCurrentWifi.ip }}
            <el-tag
              :type="
                getResponseTime < 2000
                  ? getResponseTime < 1000
                    ? 'success'
                    : 'warning'
                  : 'danger'
              "
              size="mini"
              >{{ getResponseTime }}ms</el-tag
            >
          </el-button>
          <el-button
            v-else
            class="wifi-button"
            icon="el-icon-share"
            circle
            @click="showWifi"
          ></el-button>
        </el-col>
      </el-row>
    </el-header>
    <el-main v-loading="getSending">
      <Panel v-if="getAuthStatus || !getManifest.auth" />
    </el-main>
    <el-footer>
      <div v-if="getManifest.creator">
      {{getManifest.creator}}
      </div>
      <div v-else>Email: huynhtheluat@gmail.com</div>
      </el-footer>
  </el-container>
</template>

<script>
import { mapGetters } from "vuex";
import Panel from "./Panel.vue";
export default {
  data() {
    return {
      activeIndex: "1",
      activeIndex2: "1",
    };
  },
  components: {
    Panel,
  },
  computed: {
    ...mapGetters([
      "getAuthStatus",
      "getCurrentWifi",
      "getSending",
      "getResponseTime",
      "getUptime",
      "getManifest",
    ]),
  },
  mounted: function () {
    this.$store.dispatch("requireManifestData").then(() => {
      if (this.getManifest.auth) this.$showLogin()
    });
  },
  methods: {
    showWifi: function () {
      if (this.getManifest.wifiSta) {
        this.$showWifiSelector()
      }
    },
  },
};
</script>

<style scoped>
.el-header {
  background: #545c64;
}
.wifi-button {
  display: flex;
  justify-content: end;
  align-items: center;
}
.cell {
  cursor: pointer;
}
</style>