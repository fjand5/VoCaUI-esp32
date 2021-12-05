<template>
  <div class="esp-switch">
    <ComponentWrapper
      :span="compt.props.span"
      :offset="compt.props.offset"
      :pull="compt.props.pull"
      :push="compt.props.push"
    >
      <el-button-group>
        <el-button
          :class="(espValue!= undefined) && (espValue==false) ?'':'inActive'"
          :round="compt.props.round || false"
          :size="compt.props.size || 'medium'"
          :type="compt.props.type || 'primary'"
        @click="sendCommand()"
          >off</el-button
        >
        <el-button
          :class="(espValue!= undefined) && (espValue==true)?'':'inActive'"
          :round="compt.props.round || false"
          :size="compt.props.size || 'medium'"
          :type="compt.props.type || 'primary'"
        @click="sendCommand()"
          >on</el-button
        >
      </el-button-group>
    </ComponentWrapper>
  </div>
</template>

<script>
import { mapGetters } from "vuex";

import ComponentWrapper from "./ComponentWrapper.vue";
export default {
  name: "EspSwitch",
  props: {
    compt: Object,
  },
  data: function () {
    return {
      sending: false,
      espValue: undefined,
      clientValue: undefined
    };
  },
  components: {
    ComponentWrapper,
  },
  methods: {
    sendCommand: function () {
      if(this.espValue != undefined)
        this.clientValue = !this.espValue
      else
        this.clientValue = true
      this.$sendCommand();
    },
    groupClick: function () {
      console.log("groupClick");
    },
  },
  computed: {
    ...mapGetters(["getData"]),
  },
  watch: {
    getData: function (n) {
      this.espValue = n[this.compt.espKey] == "true"
      console.log("getData", n);
    },
  },
};
</script>
<style scoped>
.el-button{
}
.inActive{
  opacity: 0.3;
}
</style>
