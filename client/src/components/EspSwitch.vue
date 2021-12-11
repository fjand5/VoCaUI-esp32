<template>
  <div class="esp-switch">
    <ComponentWrapper
      :params="compt.props"
    >
    <span class="sub-title">
    {{compt.props.name}}</span>
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
  mounted:function(){
  },

  methods: {
    sendCommand: function () {
      if(this.espValue != undefined)
        this.clientValue = !this.espValue
      else
        this.clientValue = true
      this.$sendCommand();
    },
  },
  computed: {
    ...mapGetters(["getData"]),
  },
  watch: {
    getData: function (n) {
      this.espValue = n[this.compt.espKey] == "true"
    },
  },
};
</script>
<style scoped>
span{
  margin-right: 20px;
}
.inActive{
  opacity: 0.3;
}
</style>
