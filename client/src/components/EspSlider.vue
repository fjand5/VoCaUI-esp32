<template>
  <div class="esp-slider">
    <ComponentWrapper
      :params="compt.props"
    >
      <span class="sub-title">{{ compt.props.name }} {{ espValue }}</span>
      <el-slider
        @input="sendCommand"
        v-model="clientValue"
        :debounce="100"
      ></el-slider>
    </ComponentWrapper>
  </div>
</template>

<script>
import { mapGetters } from "vuex";

import ComponentWrapper from "./ComponentWrapper.vue";
export default {
  name: "EspSlider",
  props: {
    compt: Object,
  },
  data: function () {
    return {
      sending: false,
      espValue: 0,
      clientValue: 0,

      debounceTimer: undefined,
    };
  },
  components: {
    ComponentWrapper,
  },
  methods: {
    sendCommand: function () {
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
      this.espValue = parseInt(n[this.compt.espKey]);
      this.clientValue = this.espValue;
      setTimeout(() => {
        clearTimeout(this.debounceTimer);
      }, 90);
    },
  },
};
</script>
<style scoped>
/* span{
  margin-right: 20px;
} */
.inActive {
  opacity: 0.3;
}
</style>
