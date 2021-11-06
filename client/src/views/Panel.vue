<template>
  <div class="panel">
    <el-tabs tab-position="left">
      <template v-for="(tab, index) in collectTabs">
        <el-tab-pane 
        :key="index"
        :label="tab">
          <el-row :gutter="20">
            <template v-for="(compt, index) in compts">
              <component
                :key="index"
                :is="compt.type"
                :props="compt.props"
              ></component>
            </template>
          </el-row>
        </el-tab-pane>
      </template>
    </el-tabs>
  </div>
</template>

<script>
import EspButton from "../components/EspButton";
export default {
  data() {
    return {
      compts: [
        {
          type: "EspButton",
          tab: "nhà hàng",
          props: {
            name: "nút 1",
            span: 24,
          },
        },
        {
          type: "EspButton",
          tab: "nhà hàng",
          props: {
            name: "nút 2",
            span: 12,
          },
        },
        {
          type: "EspButton",
          tab: "bếp",
          props: {
            name: "nút 3",
            span: 12,
          },
        },
      ],
    };
  },
  components: {
    EspButton,
  },
  computed: {
    collectTabs: function(){
      let ret = new Set()
      this.compts.forEach((elm)=>{
        ret.add(elm.tab)
      })
      return ret
    }
  },
  mounted: function () {},
  watch: {},
  methods: {},
};
</script>

<style scoped>
</style>