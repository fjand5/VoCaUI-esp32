<template>
  <div class="esp-input">
    <ComponentWrapper
      :span="compt.props.span"
      :offset="compt.props.offset"
      :pull="compt.props.pull"
      :push="compt.props.push"
      :newLine="compt.props.newLine"
      :divider="compt.props.divider"
    >
      <span class="sub-title">{{ compt.props.name }}</span>
      <el-row :gutter="0">
        <el-col :span="20">
          <el-input
            @focus="editting = true"
            @blur="blur"
            :placeholder="compt.props.name"
            v-model="clientValue"
          >
          </el-input>
        </el-col>
        <el-col :span="4">
          <el-button
            :type="compt.props.type || 'primary'"
            :round="compt.props.round || false"
            @click="sendCommand()"
          >
            OK
          </el-button>
        </el-col>
      </el-row>
    </ComponentWrapper>
  </div>
</template>

<script>
import { mapGetters } from "vuex";

import ComponentWrapper from "./ComponentWrapper.vue";
export default {
  name: "esp-input",
  props: {
    compt: Object,
  },
  data: function () {
    return {
      sending: false,
      espValue: undefined,
      clientValue: undefined,

      editting: false,
    };
  },
  components: {
    ComponentWrapper,
  },
  methods: {
    sendCommand: function () {
      this.$sendCommand();
    },
    blur: function () {
      setTimeout(() => {
        this.editting = false;
        this.clientValue = this.espValue;
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
      if (!this.editting) this.clientValue = this.espValue;
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
