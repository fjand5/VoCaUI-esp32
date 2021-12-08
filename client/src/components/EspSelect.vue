<template>
  <div class="esp-select">
    <ComponentWrapper :params="compt.props">
      <el-row type="flex" align="middle" :gutter="5">
        <el-col>
          <div>{{ compt.props.name }}</div>
        </el-col>
        <el-col>
          <el-select @change="$sendCommand()" v-model="clientValue" placeholder="Select">
            <el-option
              v-for="(item, index) in compt.props.options"
              :key="index"
              :label="item"
              :value="item"
            >
            </el-option>
          </el-select>
        </el-col>
      </el-row>
    </ComponentWrapper>
  </div>
</template>

<script>
import { mapGetters } from "vuex";

import ComponentWrapper from "./ComponentWrapper.vue";
export default {
  name: "esp-select",
  props: {
    compt: Object,
  },
  data: function () {
    return {
      sending: false,
      espValue: undefined,
      clientValue: null,


      options: [
        "một","hai","hai rưỡi"
      ],
    };
  },
  components: {
    ComponentWrapper,
  },
  methods: {
    sendCommand: function () {
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
