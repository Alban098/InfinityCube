'use strict';

const Controller = require('../controllers/Controller')

module.exports = router => {

    router.get('/', Controller.indexAction);
    router.get('/refresh', Controller.refreshAction);
    router.get('/fetch', Controller.fetchAction);
    router.post('/', Controller.netAction);
    router.get('/set', Controller.setAction);
    router.get('/ping', Controller.pingAction);
    router.get('/calibrate', Controller.calibrateAction)
    router.post('/config', Controller.configAction);
}