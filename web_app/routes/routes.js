'use strict';

const Controller = require('../controllers/Controller')

module.exports = router => {

    router.get('/', Controller.indexAction);
    router.get('/refresh', Controller.refreshAction);
    router.post('/', Controller.netAction)
    router.get('/set', Controller.setAction);
    router.post('/config', Controller.configAction);
}