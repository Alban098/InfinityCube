const axios = require('axios');
const net = require("net");
const ping = require("ping");

exports.address = '10.5.0.7';
exports.effets = {};
exports.palettes = {};
exports.status = {};

exports.ping = async function() {
    let result = await ping.promise.probe(this.address, {timeout: 2});
    return result.alive;
}

exports.fetchEffects = async function() {
    return axios.get("http://" + this.address + "/api?effects=0").then(res => {
        for (let effect in res.data)
            this.effets[res.data[effect]] = effect;
    }).catch(err => { console.log(err.code); });

}

exports.fetchPalettes = async function() {
    return axios.get("http://" + this.address + "/api?palettes=0").then(res => {
        for (let palette in res.data)
            this.palettes[res.data[palette]] = palette;
    }).catch(err => { console.log(err.code); });

}

exports.fetchStatus = async function() {
    return axios.get("http://" + this.address + "/api?status=0").then(res => {
        for (let status in res.data)
            this.status[status] = res.data[status];
    }).catch(err => { console.log(err.code); });
}

exports.set = async function(params) {
    if (params.primary !== undefined) {
        return axios.post("http://" + this.address + "/api", "primary_color=" + parseInt(params.primary, 16)).then(res => {
            for (let status in res.data)
                this.status[status] = res.data[status];
        }).catch(err => { console.log(err.code); });
    } if (params.secondary !== undefined) {
        return axios.post("http://" + this.address + "/api", "secondary=" + parseInt(params.secondary, 16)).then(res => {
            for (let status in res.data)
                this.status[status] = res.data[status];
        }).catch(err => { console.log(err.code); });
    } if (params.tertiary !== undefined) {
        return axios.post("http://" + this.address + "/api", "tertiary_color=" + parseInt(params.tertiary, 16)).then(res => {
            for (let status in res.data)
                this.status[status] = res.data[status];
        }).catch(err => { console.log(err.code); });
    } if (params.effect !== undefined) {
        return axios.post("http://" + this.address + "/api", "effect=" + params.effect).then(res => {
            for (let status in res.data)
                this.status[status] = res.data[status];
        }).catch(err => { console.log(err.code); });
    } if (params.speed !== undefined) {
        return axios.post("http://" + this.address + "/api", "speed=" + params.speed).then(res => {
            for (let status in res.data)
                this.status[status] = res.data[status];
        }).catch(err => { console.log(err.code); });
    } if (params.intensity !== undefined) {
        return axios.post("http://" + this.address + "/api", "intensity=" + params.intensity).then(res => {
            for (let status in res.data)
                this.status[status] = res.data[status];
        }).catch(err => { console.log(err.code); });
    } if (params.palette !== undefined) {
        return axios.post("http://" + this.address + "/api", "palette=" + params.palette).then(res => {
            for (let status in res.data)
                this.status[status] = res.data[status];
        }).catch(err => { console.log(err.code); });
    } if (params.brightness !== undefined) {
        return axios.post("http://" + this.address + "/api", "brightness=" + params.brightness).then(res => {
            for (let status in res.data)
                this.status[status] = res.data[status];
        }).catch(err => { console.log(err.code); });
    }
}

exports.setNetwork = function(ssid, pass, ip, gateway, mask) {
    if (net.isIPv4(ip) && net.isIPv4(gateway) && net.isIPv4(mask)) {
        let ip_str = ip.split(".");
        let gateway_str = gateway.split(".");
        let mask_str = mask.split(".");
        let data = "net_ssid=" + ssid + "&net_pass=" + pass;
        for (let i = 0; i < 4; i++) {
            data += "&ip_" + i + "=" + ip_str[i];
            data += "&gateway_" + i + "=" + gateway_str[i];
            data += "&mask_" + i + "=" + mask_str[i];
        }
        axios.get("http://" + this.address + "/setup?" + data).catch(err => { console.log(err.code); });
    }
}