using Prism.Events;
using Prism.Ioc;
using Prism.Regions;
using System.Windows.Controls;

namespace TMCRegisterControl.Views
{
    /// <summary>
    /// Interaction logic for TMC2590regs.xaml
    /// </summary>
    public partial class TMC2590regs : UserControl
    {
        private readonly IContainerExtension _container;
        private readonly IRegionManager _regionManager;
        private readonly IEventAggregator _ea;
        public TMC2590regs(IContainerExtension container, IRegionManager regionManager, IEventAggregator ea)
        {
            InitializeComponent();
            _container = container;
            _regionManager = regionManager;
            _ea = ea;
        }

        private void UserControl_Loaded(object sender, System.Windows.RoutedEventArgs e)
        {
            _regionManager.Regions["TMC2590readResponseRegion"].Add(_container.Resolve<TMC2590readResponse>());
            _regionManager.Regions["TMC2590DRVCTLSDOFFRegion"].Add(_container.Resolve<TMC2590DRVCTLSDOFF>());
            _regionManager.Regions["TMC2590DRVCTLSDONRegion"].Add(_container.Resolve<TMC2590DRVCTLSDON>());
            _regionManager.Regions["TMC2590CHOPCONFRegion"].Add(_container.Resolve<TMC2590CHOPCONF>());
            _regionManager.Regions["TMC2590SMARTENRegion"].Add(_container.Resolve<TMC2590SMARTEN>());
            _regionManager.Regions["TMC2590SGCSCONFRegion"].Add(_container.Resolve<TMC2590SGCSCONF>());
            _regionManager.Regions["TMC2590DRVCONFRegion"].Add(_container.Resolve<TMC2590DRVCONF>());
        }
    }
}
