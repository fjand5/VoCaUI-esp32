<template>
  <div class="esp-button">
    <ComponentWrapper
      :params="compt.props"
    >
      {{ getData[compt.espKey] }}

      <el-button
        v-if="!compt.props.confirm"
        :size="compt.props.size || 'medium'"
        :type="compt.props.type || 'primary'"
        :round="compt.props.round || false"
        @click="$sendCommand()"
        >{{ compt.props.name }}
      </el-button>
      <el-popconfirm 
      v-else
      :title="compt.props.confirm"
      @confirm="$sendCommand()"
      >
        <el-button
          slot="reference"
          :size="compt.props.size || 'medium'"
          :type="compt.props.type || 'primary'"
          :round="compt.props.round || false"
          >{{ compt.props.name }}
        </el-button>
      </el-popconfirm>
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
      clientValue: "",
      espValue: null,
    };
  },
  mounted: function () {

  },
  components: {
    ComponentWrapper,
  },
  computed: {
    ...mapGetters(["getData"]),
  },
  watch: {
    getData: function () {
      // if(n[this.compt.espKey] == )
      // console.log(n);
    },
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
