<template>
  <div class="esp-color-picker">
    <ComponentWrapper :params="compt.props">
      <el-row type="flex" align="middle" :gutter="5">
        <el-col>
          <div>{{ compt.props.name }}</div>
        </el-col>
        <el-col>
          <el-color-picker
            @active-change="sendCommand"
            v-model="clientValue"
          ></el-color-picker>
        </el-col>
      </el-row>
    </ComponentWrapper>
  </div>
</template>

<script>
import { mapGetters } from "vuex";

import ComponentWrapper from "./ComponentWrapper.vue";
export default {
  name: "esp-color-picker",
  props: {
    compt: Object,
  },
  data: function () {
    return {
      sending: false,
      espValue: undefined,
      clientValue: null,

      debounceTimer: undefined,
    };
  },
  components: {
    ComponentWrapper,
  },
  methods: {
    sendCommand: function (color) {
      const rgba = color.replace(/^rgba?\(|\s+|\)$/g, "").split(",");

      const hex = `#${(
        (1 << 24) +
        (parseInt(rgba[0]) << 16) +
        (parseInt(rgba[1]) << 8) +
        parseInt(rgba[2])
      )
        .toString(16)
        .slice(1)}`;
      this.clientValue = hex.toUpperCase();
      clearTimeout(this.debounceTimer);

      this.debounceTimer = setTimeout(() => {
        this.$sendCommand();
      }, 100);
    },
  },
  computed: {
    ...mapGetters(["getData"]),
  },
  mounted: function () {},
  watch: {
    getData: function (n) {
      this.espValue = n[this.compt.espKey];
      this.clientValue = this.espValue;
      setTimeout(() => {
        clearTimeout(this.debounceTimer);
      }, 90);
    },
  },
};
</script>
<style scoped>
span {
}
.el-col {
}
</style>
