<template>
  <div class="esp-button">
    <ComponentWrapper
      :span="compt.props.span"
      :offset="compt.props.offset"
      :pull="compt.props.pull"
      :push="compt.props.push"
    >
    {{getData[compt.espKey]}}
      <el-button
        :size="compt.props.size || 'medium'"
        :type="compt.props.type || 'primary'"
        :round="compt.props.round || true"
        @click="$sendCommand()"
        >{{ compt.props.name }} </el-button
      >
    </ComponentWrapper>
  </div>
</template>

<script>
import { mapGetters } from "vuex";
import ComponentWrapper from "./ComponentWrapper.vue";
export default {
  name: "EspButton",
  props: {
    compt: Object,
  },
  data: function () {
    return {
      sending: false,
      value: null
    };
  },
  components: {
    ComponentWrapper,
  },
  computed: {
    ...mapGetters(["getData"]),
  },
  watch:{
getData:function(n){
  // if(n[this.compt.espKey] == )
  console.log(n)
}
  },
  methods: {
    // sendCommand: function () {
    //   this.$store.dispatch("sendCommand", {
    //     espKey: this.compt.espKey,
    //     espValue: null,
    //   });
    // },
  },
};
</script>
<style scoped>
/* .el-button {
  width: 100%;
} */
</style>
