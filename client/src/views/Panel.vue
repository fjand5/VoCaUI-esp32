<template>
  <div class="panel">
    <div class="block">
      <span class="demonstration">Set Brightness</span>
      <el-slider
        @change="callSetBrightness"
        v-model="brightness"
        :min="0"
        :max="255"
        :show-input="true"
        :debounce="300"
      ></el-slider>
    </div>
    <el-button @click="callPreMode" type="primary">Previous Mode</el-button>
    <el-tag>{{ getMode }}</el-tag>
    <el-button @click="callNextMode" type="primary">Next Mode</el-button>

    <div class="block">
      <span class="demonstration">Color 1</span>
      <el-color-picker
        @change="callSetColor1"
        debounce="300"
        v-model="color1"
      ></el-color-picker>
      {{color1}}
    </div>
    <div class="block">
      <span class="demonstration">Color 2</span>
      <el-color-picker
        @change="callSetColor2"
        debounce="300"
        v-model="color2"
      ></el-color-picker>
      {{color2}}
    </div>
    <div class="block">
      <span class="demonstration">Color 3</span>
      <el-color-picker
        @change="callSetColor3"
        debounce="300"
        v-model="color3"
      ></el-color-picker>
      {{color3}}
    </div>
  </div>
</template>

<script>
import { mapGetters } from "vuex";
function convertColorNum(color) {
    let green = (color >> 16) & 0xff
    let red = (color >> 8) & 0xff
    let blue = (color >> 0) & 0xff
    return (red << 16) | (green << 8) | (blue << 0)
}
export default {
  data() {
    return {
      brightness: 0,
      speed: 0,

      color1: "0",
      color2: "0",
      color3: "0",
    };
  },
  computed: {
    ...mapGetters([
      "getMode",
      "getSpeed",
      "getBrightness",
      "getColor1",
      "getColor2",
      "getColor3",
    ]),
  },
  mounted: function () {},
  watch: {
    getBrightness: function (n) {
      this.brightness = n;
    },
    getColor1: function (n) {

      let hexString = '#' + convertColorNum(n).toString(16)
      this.color1 = hexString;
    },
    getColor2: function (n) {
      let hexString = '#' + convertColorNum(n).toString(16)
      this.color2 =hexString;
    },
    getColor3: function (n) {
      let hexString = '#' + convertColorNum(n).toString(16)
      this.color3 =hexString;
    },
  },
  methods: {
    callSetBrightness: function (val) {
      this.$store.dispatch("setBrightness", String(val));
    },
    callNextMode: function () {
      this.$store.dispatch("nextMode");
    },
    callPreMode: function () {
      this.$store.dispatch("preMode");
    },
    callSetColor1: function (val) {
      val = val.replace('#','')
      val = parseInt(val, 16)
      val = convertColorNum(val)
      this.$store.dispatch("setColor1", val);
    },
    callSetColor2: function (val) {
      val = val.replace('#','')
      val = parseInt(val, 16)
      val = convertColorNum(val)
      this.$store.dispatch("setColor2", val);
    },
    callSetColor3: function (val) {
      val = val.replace('#','')
      val = parseInt(val, 16)
      val = convertColorNum(val)
      this.$store.dispatch("setColor3", val);
    },
  },
};
</script>

<style>
</style>