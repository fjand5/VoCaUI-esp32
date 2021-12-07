<template>
  <div class="esp-input">
    <ComponentWrapper
      :span="compt.props.span"
      :offset="compt.props.offset"
      :pull="compt.props.pull"
      :push="compt.props.push"
    >
      <span class="sub-title">{{ compt.props.name }}</span>
      <el-row :gutter="0">
        <el-col :span="20">
          <el-input :placeholder="compt.props.name" v-model="espValue" clearable>
          </el-input>
        </el-col>
        <el-col :span="4">
          <el-button
            :type="compt.props.type || 'primary'"
            :round="compt.props.round || false"
            @click="$sendCommand()"
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
      espValue: 0,
    };
  },
  components: {
    ComponentWrapper,
  },
  methods: {
    sendCommand: function () {
      this.$sendCommand();
    },
  },
  computed: {
    ...mapGetters(["getData"]),
  },
  mounted: function () {},
  watch: {
    getData: function (n) {
      this.espValue = n[this.compt.espKey];

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
